inline void parseSerial() {
  if (Serial.available()) {
    //char inChar = (char)Serial.read();
    char in = (char)Serial.read();

    switch (in) {
      case '0': { //GetDistance
          int p = Serial.parseInt();
          hexy.changeServo(31, map(p, 0, 180, 501, 2499));
          hexy.delay_ms(100);
          Serial.print("0,");
          Serial.println(hexy.ping());
          break;
        }
      case '1': //Laufen, Richtung,  Geschwindigkeit, Wie weit
        //        frequenz = Serial.parseInt();
        //        richtung = Serial.parseInt();
        //        spd = Serial.parseInt();
        //        break;
      case '2': //BeginMove (Richtung, Speed)
        richtung = Serial.parseInt();
        spd = Serial.parseInt();
        break;

      case '3': //EndMove()
        spd = 0;
        break;

      case '4': //Aufstehen
        standUp();
        Serial.println(4);
        break;

      case '5':
        layDown();
        Serial.println(5);
        break;

      case '6':
        hexy.changeServo(Serial.parseInt(), map(Serial.parseInt(), 0, 180, 501, 1499));
        break;

      case '7':
        richtung = Serial.parseInt();
        spd = Serial.parseInt();
        break;

      case '8':
        layForward(Serial.parseInt());
        Serial.println(8);
        break;

      case 'B': //Alle Beine ausstrecken.
        for (int  i = 5; i < 31; i++) {
          hexy.changeServo(i, 1500);
        }
        break;

      case 'A': //Servos abschalten.
        for (int  i = 5; i < 32; i++) {
          hexy.changeServo(i, -1);
        }
        break;

      default:
        //Alles andere >> MÜll
        break;
    }
  }
}
