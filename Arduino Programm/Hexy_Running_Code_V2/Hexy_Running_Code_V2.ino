#include "Servotor32.h" // call the servotor32 Library
Servotor32 hexy;

unsigned long previousMillis = 0;
long interval = 10;

unsigned long millisekunden = 0;

const int schrittweiteMin = 1300;
const int schrittweiteMax = 1900;

const int beinHoeheMin = 2000; //Kleiner -> Höher
const int beinHoeheMax = 2350; //Größer -> Tiefer

const int fussHoeheMin = 900;
const int fussHoeheMax = 1400;

double frequenz = 0;
int spd = 8;

int richtung = 0;

unsigned int zyklusCounter = 0;

void setup() {
  hexy.begin();

  //standUp();
  //hexy.delay_ms(60000);


}


void loop() {

  parseSerial();

  //Um Prozessorzeit für anderes zu sparen und die Servos nicht unnötig zu aktualisieren hier eine Art Timer
  unsigned long currentMillis = hexy.millis_new();
  if (currentMillis - previousMillis >= interval && frequenz != 0) {
    previousMillis = currentMillis;
    run(richtung, frequenz);
  }
}

inline void run(int richtung, int frequenz) {
  //  if (frequenz > 4)
  //    frequenz = 4;
  //  if (frequenz < -4)
  //    frequenz = -4;

  //millisekunden = hexy.millis_new();
  millisekunden += spd;


  //Horizontal

  int sinus = 180 * sin(6.28 * frequenz * millisekunden);
  int beinPos1 = map(sinus, -180, 180, schrittweiteMin + richtung, schrittweiteMax);
  int beinPos2 = map(sinus, -180, 180, schrittweiteMax, schrittweiteMin - richtung);
  //Vertikal
  sinus = 180 * sin(6.28 * frequenz * millisekunden + 1.57);
  int beinHoehe1 = map(sinus, -180, 180, beinHoeheMin, beinHoeheMax);
  int beinHoehe2 = map(sinus, -180, 180, beinHoeheMax, beinHoeheMin);
  //Füße
  int fussPos1 = map(beinHoehe1, beinHoeheMin, beinHoeheMax, fussHoeheMin, fussHoeheMax); //map(180*sin(2*3.14*speed*hexy.millis_new()+1.57),-180,180,1100,1500);
  int fussPos2 = map(beinHoehe2, beinHoeheMin, beinHoeheMax, fussHoeheMin, fussHoeheMax); //map(180*sin(2*3.14*speed*hexy.millis_new()+1.57),-180,180,1500,1100);


  //Vorderfüße
  hexy.changeServo(7, map(3000 - beinPos1, schrittweiteMin, schrittweiteMax, 1200, 1700));
  hexy.changeServo(24, map(beinPos2, schrittweiteMin, schrittweiteMax, 1200, 1700));

  //Füße Mittig
  hexy.changeServo(20, beinPos1);
  hexy.changeServo(11, 3000 - beinPos2);

  //Hinterläufe
  hexy.changeServo(15, 3000 - beinPos1);
  hexy.changeServo(16, beinPos2);

  //hexy.delay_ms(100);

  //Vertikal
  //Vorne
  hexy.changeServo(6, beinHoehe1);
  hexy.changeServo(25, beinHoehe2);


  //Mitte
  hexy.changeServo(21, beinHoehe1);
  hexy.changeServo(10, beinHoehe2);

  //Hinten
  hexy.changeServo(14, beinHoehe1);
  hexy.changeServo(17, beinHoehe2);


  //Füße in Position bringen
  //Vorne
  hexy.changeServo(5, fussPos1);
  hexy.changeServo(26, fussPos2);

  //Mitte
  hexy.changeServo(9, fussPos2);
  hexy.changeServo(22, fussPos1);

  //Hinten
  hexy.changeServo(13, fussPos1);
  hexy.changeServo(18, fussPos2);
}

inline void parseSerial() {
  if (Serial.available()) {
    char inChar = (char)Serial.read();
    switch (inChar) {
      case '0':
        frequenz = 0;
        Serial.println(frequenz);
        break;
      case '+':
        frequenz++;
        Serial.println(frequenz);
        break;
      case '-':
        frequenz--;
        Serial.println(frequenz);
        break;

      case 'a':
        richtung += 10;
        Serial.println(richtung);
        break;
      case 'd':
        richtung -= 10;
        Serial.println(richtung);
        break;

      case 'z':
        interval += 5;
        Serial.println(interval);
        break;
      case 'h':
        interval -= 5;
        Serial.println(interval);
        break;

      case 's':
        spd = Serial.parseInt();
        Serial.print("Speed: ");
        Serial.println(spd);
        break;

      case 'u':
        standUp();
        break;

      case 'f': //flat
        for (int i = 5; i < 31; i++)
          hexy.changeServo(i, 1500);
        break;

      default:
        break;
    }
  }
}

void standUp() {
  //Alle Beine zusammenfahren
  hexy.changeServo(7, 1800);
  hexy.changeServo(11, 1500);
  hexy.changeServo(15, 1200);
  hexy.changeServo(16, 1800);
  hexy.changeServo(20, 1500);
  hexy.changeServo(24, 1200);
  hexy.delay_ms(500);

  //Beine
  hexy.changeServo(6, 600);
  hexy.changeServo(10, 600);
  hexy.changeServo(14, 600);
  hexy.changeServo(17, 600);
  hexy.changeServo(21, 600);
  hexy.changeServo(25, 600);
  hexy.delay_ms(500);

  //Füße nach unten
  hexy.changeServo(5, 600);
  hexy.changeServo(9, 600);
  hexy.changeServo(13, 600);
  hexy.changeServo(18, 600);
  hexy.changeServo(22, 600);
  hexy.changeServo(26, 600);
  hexy.delay_ms(500);

  for (int i = 900; i < 1600; i += 20) {

    //Beine nach unten fahren
    hexy.changeServo(6, i);
    hexy.changeServo(10, i);
    hexy.changeServo(14, i);
    hexy.changeServo(17, i);
    hexy.changeServo(21, i);
    hexy.changeServo(25, i);
    //Füße unten halten
    int angle = map(i, 900, 1600, 500, 600);
    hexy.changeServo(5, angle);
    hexy.changeServo(9, angle);
    hexy.changeServo(13, angle);
    hexy.changeServo(18, angle);
    hexy.changeServo(22, angle);
    hexy.changeServo(26, angle);
  }

  hexy.delay_ms(500);
  for (int j = 0; j < 1; j++) {
    //Letzendlich komplett aufrichten
    hexy.changeServo(6, 900);
    hexy.changeServo(14, 900);
    hexy.changeServo(21, 900);
    hexy.delay_ms(500);

    for (int i = 900; i < 2350; i += 20) {
      hexy.changeServo(6, i);
      hexy.changeServo(14, i);
      hexy.changeServo(21, i);


      int angle = map(i, 900, 2350, 500, 1400);
      hexy.changeServo(5, angle);
      hexy.changeServo(13, angle);
      hexy.changeServo(22, angle);
    }
    hexy.delay_ms(500);

    //Andere Seite
    hexy.changeServo(25, 900);
    hexy.changeServo(17, 900);
    hexy.changeServo(10, 900);
    hexy.delay_ms(500);

    for (int i = 900; i < 2350; i += 20) {
      hexy.changeServo(25, i);
      hexy.changeServo(17, i);
      hexy.changeServo(10, i);

      int angle = map(i, 900, 2350, 500, 1400);
      hexy.changeServo(26, angle);
      hexy.changeServo(18, angle);
      hexy.changeServo(9, angle);
    }
  }

}

