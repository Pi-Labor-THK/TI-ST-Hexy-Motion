
//Update()                        - Prüft, ob es an der Zeit ist die Servos zu aktualiseren
//Run(int richtung, int frequenz) - Lässt die Hexy in die entsprehende Richtung laufen. Die Frequenz kann geändert werden, aber bei 1 ist die Bewegung am flüssigsten.

//Use virtual Timer to check whether an update for the servos is needed.
inline void update() {
  //Set up servos with 50Hz. Updating more often steals response time from serial communication
  unsigned long currentMillis = hexy.millis_new();
  if (currentMillis - previousMillis >= interval && spd != 0) {
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
