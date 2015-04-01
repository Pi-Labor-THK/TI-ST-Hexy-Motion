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

  for (int i = 900; i < 1800; i += 40) {

    //Beine nach unten fahren
    hexy.changeServo(6, i);
    hexy.changeServo(10, i);
    hexy.changeServo(14, i);
    hexy.changeServo(17, i);
    hexy.changeServo(21, i);
    hexy.changeServo(25, i);
    //Füße unten halten
    int angle = map(i, 900, 1800, 500, 600);
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

    for (int i = 900; i < 2350; i += 40) {
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
