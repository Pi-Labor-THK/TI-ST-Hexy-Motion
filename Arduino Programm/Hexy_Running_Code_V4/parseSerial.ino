inline void parseSerial() {
  if (Serial.available()) {
    //char inChar = (char)Serial.read();
    char in = (char)Serial.read();

    switch (in) {
      case '0': { //GetDistance
          int p = Serial.parseInt();
          hexy.changeServo(31, map(p, 0, 180, 501, 2499));
          hexy.delay_ms(500);
          Serial.print("0,");
          Serial.println(hexy.ping());
          break;
        }

      case '2': //Laufen, Richtung,  Geschwindigkeit
        frequenz = Serial.parseInt();
        richtung = Serial.parseInt();
        spd = Serial.parseInt();
        break;

      case '3': //Stehen bleiben
        frequenz = 0;
        break;

      case '4': //Aufstehen
        standUp();
        break;

      case '7': //Alle Beine ausstrecken.
        for (int  i = 5; i < 31; i++) {
          hexy.changeServo(i, 1500);
        }
        break;

      case '8': //Servos abschalten.
        for (int  i = 5; i < 32; i++) {
          hexy.changeServo(i, -1);
        }
        Serial.println(8);
        break;

      default:
        break;
    }
  }
}
