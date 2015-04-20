//turn(int degree)           - Dreht um "degree"-Grad auf der Stelle. //Achtung fehlendes Finetuning!
//disableServos()            - Schaltet alle Servos gnadenlos ab
//standUp()                  - Hexy steht auf
//standUpFull()              - Hexy richtet sich komplett auf und zentriert die Beine
//layForward(int degree)     - Hexy lehnt sich um die Gradzahl nach vorne
//layDown();                 - Hexy hat genug...

void layDown() {
  hexy.changeServo(24, 1500);
  hexy.changeServo(20, 1500);
  hexy.changeServo(16, 1500);
  hexy.changeServo(15, 1500);
  hexy.changeServo(11, 1500);
  hexy.changeServo(7, 1500);

  for (int i = 2400; i > 500; i -= 20) {
    hexy.changeServo(25, i);
    hexy.changeServo(21, i);
    hexy.changeServo(17, i);
    hexy.changeServo(14, i);
    hexy.changeServo(10, i);
    hexy.changeServo(6, i);

    if (i > 1500) {
      int footValue = map(i, 2400, 1500, 1500, 500);
      hexy.changeServo(26, footValue);
      hexy.changeServo(22, footValue);
      hexy.changeServo(18, footValue);
      hexy.changeServo(13, footValue);
      hexy.changeServo(9, footValue);
      hexy.changeServo(5, footValue);
    }
    if (i < 1000) {
      int footValue = map(i, 1000, 500, 500, 2450);
      hexy.changeServo(26, footValue);
      hexy.changeServo(22, footValue);
      hexy.changeServo(18, footValue);
      hexy.changeServo(13, footValue);
      hexy.changeServo(9, footValue);
      hexy.changeServo(5, footValue);
    }
  }

//Winke zum Abschied
  hexy.changeServo(7, 500);
  hexy.changeServo(6, 700);
  
  for (int i = 1500; i > 500; i-=6)
    hexy.changeServo(5, i);
  for (int i = 500; i < 1500; i+=6)
    hexy.changeServo(5, i);
  for (int i = 1500; i > 500; i-=6)
    hexy.changeServo(5, i);
  for (int i = 500; i < 1500; i+=6)
    hexy.changeServo(5, i);

hexy.changeServo(7,1500);
hexy.changeServo(5,2450);
hexy.changeServo(6,500);

  hexy.delay_ms(1000);
  disableServos();

}

void layForward(int degree) {

  //Hintere Füße in Position bringen
  hexy.changeServo(14, 2000);
  hexy.changeServo(17, 2000);
  hexy.changeServo(13, 1250);
  hexy.changeServo(18, 1250);
  hexy.delay_ms(128);
  hexy.changeServo(14, 2400);
  hexy.changeServo(17, 2400);

  //Mittlere Füße in Poition bringen
  hexy.changeServo(10, 2000);
  hexy.changeServo(21, 2000);
  hexy.changeServo(9, 1250);
  hexy.changeServo(22, 1250);
  hexy.delay_ms(128);
  hexy.changeServo(10, 2400);
  hexy.changeServo(21, 2400);
  hexy.delay_ms(128);

  //Vordere Füße
  hexy.changeServo(25, 2000);
  hexy.changeServo(6, 2000);
  hexy.changeServo(26, 1250);
  hexy.changeServo(5, 1250);
  hexy.changeServo(24, 2000);
  hexy.changeServo(7, 1000);
  hexy.delay_ms(128);
  hexy.changeServo(25, 2400);
  hexy.changeServo(6, 2400);


  for (int i = 2400; i > degree; i -= 10) {
    hexy.changeServo(25, i);
    hexy.changeServo(6, i);
    hexy.changeServo(26, map(i, 2400, degree, 1250, map(degree, 2400, 900, 1250, 500)));
    hexy.changeServo(5, map(i, 2400, degree, 1250, map(degree, 2400, 900, 1250, 500)));

    //Mittlere Servos
    int temp = map(i, 2400, degree, 2400, (2400 + degree) / 2); //Die mittleren Servos fahren nur die hälfte runter!
    hexy.changeServo(10, temp);
    hexy.changeServo(21, temp);
    hexy.changeServo(22, map(temp, 2400, (2400 + degree) / 2, 1250, map(degree, 2400, 900, 1250, 600)));
    hexy.changeServo(9, map(temp, 2400, (2400 + degree) / 2, 1250, map(degree, 2400, 900, 1250, 600)));
  }
}

void turn(int degree) { //- means left, + means right
  //turnRange von 3000 entspricht (leider nur) ungefähr 90°
  int turnSpeed = 60;
  int legUp = 2000;
  int legDown = 2350;
  int footUp = 900;
  int footDown = 1400;
  int maxTurn = 600;
  int turnRange;
  int tempTurnRange = map(degree, -360, 360, 12000, -12000);
  int split = 0;
  int remaining = 0;

  if (tempTurnRange > maxTurn || tempTurnRange < -maxTurn) {
    split = abs(tempTurnRange / maxTurn);

    remaining = tempTurnRange % maxTurn;
    if (tempTurnRange > 0)
      turnRange = maxTurn;
    else
      turnRange = -maxTurn;
  }
  else {
    split = 1;
    turnRange = tempTurnRange;
  }

  for (int m = 0; m < split; m++) {
    //Beim Mitte-Links
    hexy.changeServo(10, legUp);
    hexy.changeServo(9, footUp);
    hexy.changeServo(17, legUp);
    hexy.changeServo(18, footUp);
    hexy.changeServo(25, legUp);
    hexy.changeServo(26, footUp);


    hexy.changeServo(11, 1500 + turnRange / 2);
    hexy.changeServo(16, 1500 + turnRange / 2);
    hexy.changeServo(24, 1500 + turnRange / 2);
    hexy.delay_ms(100);

    hexy.changeServo(10, legDown);
    hexy.changeServo(9, footDown);
    hexy.changeServo(17, legDown);
    hexy.changeServo(18, footDown);
    hexy.changeServo(25, legDown);
    hexy.changeServo(26, footDown);
    hexy.delay_ms(100);

    hexy.changeServo(14, legUp);
    hexy.changeServo(13, footUp);
    hexy.changeServo(21, legUp);
    hexy.changeServo(22, footUp);
    hexy.changeServo(6, legUp);
    hexy.changeServo(5, footUp);
    hexy.delay_ms(100);

    hexy.changeServo(7, 1500 + turnRange / 2);
    hexy.changeServo(15, 1500 + turnRange / 2);
    hexy.changeServo(20, 1500 + turnRange / 2);
    hexy.delay_ms(100);

    if (turnRange > 0)
      for (int i = 1500 + turnRange / 2; i > 1500 - turnRange / 2; i -= turnSpeed) {

        hexy.changeServo(11, i);
        hexy.changeServo(16, i);
        hexy.changeServo(24, i);
      }
    if (turnRange < 0) {
      for (int i = 1500 + turnRange / 2; i < 1500 - turnRange / 2; i += turnSpeed) {

        hexy.changeServo(11, i);
        hexy.changeServo(16, i);
        hexy.changeServo(24, i);
      }
    }

    hexy.delay_ms(100);
    hexy.changeServo(14, legDown);
    hexy.changeServo(13, footDown);
    hexy.changeServo(6, legDown);
    hexy.changeServo(5, footDown);
    hexy.changeServo(21, legDown);
    hexy.changeServo(22, footDown);

    hexy.delay_ms(100);

    hexy.changeServo(10, legUp);
    hexy.changeServo(9, footUp);
    hexy.changeServo(17, legUp);
    hexy.changeServo(18, footUp);
    hexy.changeServo(25, legUp);
    hexy.changeServo(26, footUp);
    hexy.delay_ms(100);

    if (turnRange > 0)
      for (int i = 1500 + turnRange / 2; i > 1500 - turnRange / 2; i -= turnSpeed) {

        hexy.changeServo(15, i);
        hexy.changeServo(7, i);
        hexy.changeServo(20, i);
      }
    if (turnRange < 0) {
      for (int i = 1500 + turnRange / 2; i < 1500 - turnRange / 2; i += turnSpeed) {

        hexy.changeServo(15, i);
        hexy.changeServo(7, i);
        hexy.changeServo(20, i);
      }
    }

    hexy.changeServo(10, legDown);
    hexy.changeServo(9, footDown);
    hexy.changeServo(17, legDown);
    hexy.changeServo(18, footDown);
    hexy.changeServo(25, legDown);
    hexy.changeServo(26, footDown);
  }

  if (remaining != 0)
    turn(map(remaining, 12000, -12000, -360, 360));
}

//***************************************************************************


void disableServos() {

  for (int  i = 5; i < 32; i++) {
    hexy.changeServo(i, -1);
  }
}

//***************************************************************************


void standUp() { //Ready to use.
  int standUpSpeed = 50;

  for (int  i = 5; i < 31; i++) {
    hexy.changeServo(i, 1500);
  }
  hexy.delay_ms(200);
  //Alle Beine zusammenfahren
  hexy.changeServo(7, 1800);
  hexy.changeServo(11, 1500);
  hexy.changeServo(15, 1200);
  hexy.changeServo(16, 1800);
  hexy.changeServo(20, 1500);
  hexy.changeServo(24, 1200);
  //hexy.delay_ms(500);

  //Beine
  hexy.changeServo(6, 600);
  hexy.changeServo(10, 600);
  hexy.changeServo(14, 600);
  hexy.changeServo(17, 600);
  hexy.changeServo(21, 600);
  hexy.changeServo(25, 600);
  //hexy.delay_ms(500);

  //Füße nach unten
  hexy.changeServo(5, 500);
  hexy.changeServo(9, 500);
  hexy.changeServo(13, 500);
  hexy.changeServo(18, 500);
  hexy.changeServo(22, 500);
  hexy.changeServo(26, 500);
  hexy.delay_ms(60);

  for (int i = 900; i < 1800; i += standUpSpeed * 2) {

    //Beine nach unten fahren
    hexy.changeServo(6, i);
    hexy.changeServo(10, i);
    hexy.changeServo(14, i);
    hexy.changeServo(17, i);
    hexy.changeServo(21, i);
    hexy.changeServo(25, i);
    //Füße unten halten

    if (i > 1400) {
      int angle = map(i, 1400, 1800, 500, 800);
      hexy.changeServo(5, angle);
      hexy.changeServo(9, angle);
      hexy.changeServo(13, angle);
      hexy.changeServo(18, angle);
      hexy.changeServo(22, angle);
      hexy.changeServo(26, angle);
    }
  }
  standUpFull(standUpSpeed);
}


//***************************************************************************
void standUpFull(int standUpSpeed) {

  //Letzendlich komplett aufrichten
  hexy.changeServo(6, 1500);
  hexy.changeServo(14, 1500);
  hexy.changeServo(21, 1500);

  hexy.changeServo(7, 1500);
  hexy.changeServo(15, 1500);
  hexy.changeServo(20, 1500);
  //hexy.delay_ms(500);

  for (int i = 1500; i < 2000; i += standUpSpeed) {
    hexy.changeServo(6, i);
    hexy.changeServo(14, i);
    hexy.changeServo(21, i);

    int angle = map(i, 1500, 2400, 500, 1500);
    hexy.changeServo(5, angle);
    hexy.changeServo(13, angle);
    hexy.changeServo(22, angle);
  }

  //Andere Seite
  hexy.changeServo(25, 1500);
  hexy.changeServo(17, 1500);
  hexy.changeServo(10, 1500);

  hexy.changeServo(24, 1500);
  hexy.changeServo(16, 1500);
  hexy.changeServo(11, 1500);
  //hexy.delay_ms(100);

  for (int k = 2000; k < 2400; k += standUpSpeed) {
    hexy.changeServo(25, k);
    hexy.changeServo(17, k);
    hexy.changeServo(10, k);

    int angle = map(k, 2000, 2400, 500, 1500);
    hexy.changeServo(26, angle);
    hexy.changeServo(18, angle);
    hexy.changeServo(9, angle);
  }
  //hexy.delay_ms(100);
  for (int i = 2000; i < 2400; i += standUpSpeed) {
    hexy.changeServo(6, i);
    hexy.changeServo(14, i);
    hexy.changeServo(21, i);

    int angle = map(i, 1500, 2400, 500, 1500);
    hexy.changeServo(5, angle);
    hexy.changeServo(13, angle);
    hexy.changeServo(22, angle);
  }
}

