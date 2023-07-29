
class claseBeeps {
private:
  byte pin;

public:
  //---------------------------------
  claseBeeps(byte pinBuzzer) {
    this->pin = pinBuzzer;
  }

  //---------------------------------
  void hacerBeep(int tiempo1, int tiempo2, byte i = 1) {
    for (byte x = 1; x <= i; x++) {
      //digitalWrite(this->pin, HIGH);
      tone(this->pin, tonoHzBeep, tiempo1);
      delay(tiempo1);
      //digitalWrite(this->pin, LOW);
      noTone(this->pin);
      delay(tiempo2);
    }
  }
  //---------------------------------
  void dosMasTres(byte i = 1) {
    for (byte vecesBeep = 1; vecesBeep <= i; vecesBeep++) {
      hacerBeep(250, 50, 1);
      hacerBeep(250, 100, 1);
      hacerBeep(75, 10, 1);
      hacerBeep(120, 50, 1);
      hacerBeep(120, 200, 1);
    }
  }
  //---------------------------------
  void SOS(byte i = 1) {
    for (byte vecesBeep = 1; vecesBeep <= i; vecesBeep++) {
      hacerBeep(75, 75, 2);
      hacerBeep(75, 250, 1);
      hacerBeep(250, 75, 2);
      hacerBeep(250, 250, 1);
      hacerBeep(75, 75, 2);
      hacerBeep(75, 500, 1);
    }
  }
  //---------------------------------
  void punto(byte i = 1) {
    for (byte x = 1; x <= i; x++) {
      hacerBeep(75, 75, 1);
    }
  }
  //---------------------------------
  void ralla(byte i = 1) {
    for (byte x = 1; x <= i; x++) {
      hacerBeep(250, 75, 1);
    }
  }
  //---------------------------------
  void espacio(byte i = 1) {
    for (byte x = 1; x <= i; x++) {
      delay(250);
    }
  }
  //---------------------------------
  void ok(byte i = 1) {
    for (byte n = 1; n <= i; n++) {
      ralla(3);
      espacio();
      ralla();
      punto();
      ralla();
      espacio();
    }
  }

  void TonoLargo(byte i = 1) {
    for (byte n = 1; n <= i; n++) {
      hacerBeep(1000, 1, 1);
     
    }
  }
  //---------------------------------

  //---------------------------------
  void evaluar(byte buzzerMode) {

//     Serial.print("Modo ");         // Con fines de depuracion
//     Serial.println(buzzerMode);    // Con fines de depuracion

    switch (buzzerMode) {
      case 1:  //un beep corto
        Serial.println(" un Beep corto");
        //tone(buzzerPin,tonoHzBeep,125);
        hacerBeep(100, 500);
        break;

      case 2:  //dos pitos cortos
        Serial.println(" dos Pitidos Cortos");
        hacerBeep(100, 100, 2);
        break;
      case 3:
        Serial.println(" 15 Beeps cortos");
        hacerBeep(75, 50, 15);
        break;

      case 4:
        Serial.println(" dos beeps largos y tres cortos");
        dosMasTres(2);
        break;

      case 5:
        Serial.println(" SOS");
        SOS();
        break;

      case 6:
        Serial.println(" ok");
        ok();
        break;

      case 7:
        Serial.println(" Tono Largo");
        TonoLargo();
        break;
    }
  }
  //---------------------------------
};
claseBeeps Beeps(buzzerPin);

//--------------------------------------------------------