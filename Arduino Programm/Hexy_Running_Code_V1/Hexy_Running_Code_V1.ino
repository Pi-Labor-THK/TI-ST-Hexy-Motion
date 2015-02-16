#include "Servotor32.h" // call the servotor32 Library
Servotor32 hexy;

unsigned long previousMillis = 0;
long interval = 80;

unsigned long millisekunden = 0;

const int schrittweiteMin = 1300;
const int schrittweiteMax = 1900;

const int beinHoeheMin = 2000; //Kleiner -> Höher
const int beinHoeheMax = 2350; //Größer -> Tiefer

const int fussHoeheMin = 900;
const int fussHoeheMax = 1400;

double frequenz = 1;

int richtung = 0;

void setup() {
  hexy.begin();
}


void loop() {
  parseSerial();

//Um Prozessorzeit für anderes zu sparen und die Servos nicht unnötig zu aktualisieren hier eine Art Timer
  unsigned long currentMillis = hexy.millis_new();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    run(richtung, frequenz); //Frequenz = Geschwindigkeit von 0-4
  }
}

void run(int richtung, int frequenz) {
  if (frequenz > 4)
    frequenz = 4;
  if (frequenz < -4)
    frequenz = -4;

  //millisekunden = hexy.millis_new();
  millisekunden++;

  //Horizontal
  int beinPos1 = map(180 * sin(2 * 3.14 * frequenz * millisekunden), -180, 180, schrittweiteMin, schrittweiteMax);
  int beinPos2 = map(180 * sin(2 * 3.14 * frequenz * millisekunden), -180, 180, schrittweiteMax, schrittweiteMin);
  //Vertikal
  int beinHoehe1 = map(180 * sin(2 * 3.14 * frequenz * millisekunden + 3.14 / 2), -180, 180, beinHoeheMin, beinHoeheMax);
  int beinHoehe2 = map(180 * sin(2 * 3.14 * frequenz * millisekunden + 3.14 / 2), -180, 180, beinHoeheMax, beinHoeheMin);
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

void parseSerial() {
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

      default:
        break;
    }
  }
}





