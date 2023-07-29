#include "init.h"
#include "Beeps.h"
#include "func.h"

void setup() {
#ifndef ESP8266
  while (!Serial)
    ;  // wait for serial port to connect. Needed for native USB
#endif

  pinMode(buzzerPin, OUTPUT);
  pinMode(relePin, OUTPUT);

  Serial.begin(9600);  // Establece la velocidad de datos del puerto serie
  iniciarLCD();
  revisarRTC();
  Serial.println("Iniciando sistema");
  Beeps.evaluar(1);
  lcd.setCursor(0, 1);
  delay(10);

  sr.setDelayScroll(delayPersonalizado);
  String data = "HOLA";
  sr.print(&data);
  delay(500);
}

void loop() {
  buzzerMode = map(analogRead(A1), 1, 1023, 0, 10);
  Beeps.evaluar(buzzerMode);
  // lcd.setCursor(14, 1);
  // lcd.print(buzzerMode);
  // HoraMonitorSerial();
  HoraLcd();
  HoraSr();
  evaluarHorarioAlarma();
  delay(10);
}