#include "init.h"
//#include "Beeps.h"
#include "func.h"

void setup() {
#ifndef ESP8266
  while (!Serial)
    ;  // wait for serial port to connect. Needed for native USB
#endif

  EasyBuzzer.setPin(buzzerPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relePin, OUTPUT);

  Serial.begin(9600);  // Establece la velocidad de datos del puerto serie
  iniciarLCD();
  revisarRTC();
  Saludos();
}

void loop() {
  EasyBuzzer.update();
  //  buzzerMode = map(analogRead(A1), 1, 1023, 0, 10);
  // Beeps.evaluar(buzzerMode);

 //  buzzerMode = map(analogRead(A1), 1, 1023, 0, 10);
 //  Beep(buzzerMode);

  // lcd.setCursor(14, 1);
  // lcd.print(buzzerMode);
  // HoraMonitorSerial();
  HoraLcd();
  HoraSr();
  evaluarHorarioAlarma();
  delay(10);
}