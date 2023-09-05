#include "Arduino.h"

void MyBeep(byte modo) {
  Serial.println(modo);

  switch (buzzerMode) {
    case 1:  //un beep corto
      Serial.println(" un Beep corto");
      EasyBuzzer.beep(
        tonoHzBeep,  // Frecuencia en herzios
        100,         // Duración beep en ms
        500,         // Duración silencio en ms
        1,           // Números de beeps por ciclos
        500,         // Duración de la pausa
        1            // Número de ciclos
        //  sonidoTerminado// Función callback que es llamada cuando termina
      );
      //tone(buzzerPin,tonoHzBeep,125);
      // hacerBeep(100, 500);
      break;

    case 2:  //dos pitos cortos
      Serial.println(" dos Pitidos Cortos");
      //hacerBeep(100, 100, 2);
      EasyBuzzer.beep(
        tonoHzBeep,  // Frecuencia en herzios
        100,         // Duración beep en ms
        100,         // Duración silencio en ms
        2,           // Números de beeps por ciclos
        500,         // Duración de la pausa
        1            // Número de ciclos
                     //  sonidoTerminado// Función callback que es llamada cuando termina
      );

      break;
    case 3:
      Serial.println(" 15 Beeps cortos");
      //hacerBeep(75, 50, 15);
      break;

    case 4:
      Serial.println(" dos beeps largos y tres cortos");
      //dosMasTres(2);
      break;

    case 5:
      Serial.println(" SOS");
      //SOS();
      break;

    case 6:
      Serial.println(" ok");
      //ok();
      break;

    case 7:
      Serial.println(" Tono Largo");
      //TonoLargo();
      break;
  }
}



void Saludos() {
  Serial.println("Iniciando sistema");
  // Beeps.evaluar(1);
  EasyBuzzer.beep(
    tonoHzBeep,  // Frecuencia en herzios
    100,         // Duración beep en ms
    100,         // Duración silencio en ms
    1,           // Números de beeps por ciclos
    300,         // Duración de la pausa
    1            // Número de ciclos
    //  sonidoTerminado// Función callback que es llamada cuando termina
  );
  lcd.setCursor(0, 1);
  lcd.setCursor(6, 0);
  lcd.print(Saludo_inicial);
  delay(10);
  sr.setDelayScroll(delayPersonalizado);
  String data = Saludo_inicial;
  sr.print(&data);
  delay(150);
  EasyBuzzer.stopBeep();
  delay(350);
  data = Version;
  sr.print(&data);
  lcd.setCursor(5, 1);
  lcd.print(Version);
  EasyBuzzer.update();
  delay(2000);
  // EasyBuzzer.stopBeep();
}

DateTime leerFechaHora(bool leerFechaModoManual = 0) {
  if (leerFechaModoManual) {
    FechaHora = (fechaManual + (millis() / velocidadHoraManual));
  } else {
    FechaHora = rtc.now();  //obtenemos la hora y FechaHora actual
  }
  return FechaHora;
  //---------------------------------
}
//---------------------------------
void evaluarHorarioAlarma() {
  // lcd.setCursor(14, 1);
  // lcd.print(sono);
  if (FechaHora.minute() > 55 && FechaHora.minute() < 59 /*FechaHora.second() == 50*/) {
    sono = 0;
    // tone(buzzerPin, tonoHzBeep, 125);
  }
  leerFechaHora(leerFechaModoManual);
  if (sonarHorasPunto) {
    if (sonarSemanaHorasPunto) {
      if (sonarSoloLaboralHorasPunto) {
        //codigo 111
        if (((FechaHora.dayOfTheWeek()) >= 1 && (FechaHora.dayOfTheWeek() <= 5) && FechaHora.hour() >= 8 && FechaHora.hour() <= 18 && FechaHora.minute() == 0 && FechaHora.second() <= 59 && sono == 0)) {
          //beep(1);
          sono = 1;
          //  Beeps.evaluar(1);

          buzzerMode = 1;
          MyBeep(buzzerMode);
        }
      } else {
        //codigo 110
        if (((FechaHora.dayOfTheWeek()) >= 1 && (FechaHora.dayOfTheWeek() <= 5) && FechaHora.minute() == 0 && FechaHora.second() <= 59 && sono == 0)) {
          //beep(1);
          sono = 1;
          //  Beeps.evaluar(1);

          buzzerMode = 1;
          MyBeep(buzzerMode);
        }
      }
    } else {
      if (sonarSoloLaboralHorasPunto) {
        //codigo 101
        if (FechaHora.hour() >= 8 && FechaHora.hour() <= 18 && FechaHora.minute() == 0 && FechaHora.second() <= 59 && sono == 0) {
          //beep(1);
          sono = 1;
          // Beeps.evaluar(1);

          buzzerMode = 1;
          MyBeep(buzzerMode);
        }
      } else {
        //codigo 100
        if (FechaHora.minute() == 0 && FechaHora.second() <= 59 && sono == 0) {
          //     Beeps.evaluar(1);
          buzzerMode = 1;
          MyBeep(buzzerMode);

          sono = 1;
        }
      }
    }
  }
}
//---------------------------------


void HoraMonitorSerial() {

  leerFechaHora(leerFechaModoManual);

  segundo = FechaHora.second();
  minuto = FechaHora.minute();
  hora = FechaHora.hour();
  dia = FechaHora.day();
  mes = FechaHora.month();
  anio = FechaHora.year();
  diaDeLaSemana = FechaHora.dayOfTheWeek();

  //Enviamos por el puerto serie la hora y FechaHora.
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print(" , ");
  Serial.print(nombreDia[diaDeLaSemana]);
  Serial.print(" ");
  Serial.print(dia);
  Serial.print(" de ");
  Serial.print(nombreMes[mes - 1]);
  Serial.print(" del ");
  Serial.print(anio);
  Serial.print("------------------- UNIX TIME   :");
  Serial.print((FechaHora.unixtime()));
  Serial.println();
}
//---------------------------------
void HoraLcd() {

  leerFechaHora(leerFechaModoManual);


  segundo = FechaHora.second();
  minuto = FechaHora.minute();
  hora = FechaHora.hour();
  dia = FechaHora.day();
  mes = FechaHora.month();
  anio = FechaHora.year();
  diaDeLaSemana = FechaHora.dayOfTheWeek();
  //-------------------------------
  if (DiaAnterior != dia) {
    lcd.clear();
    DiaAnterior = dia;
    //beep(1); Se usó para verificar que limpiaba la pantalla diariamente
  }
  lcd.setCursor(0, 0);
  lcd.print(nombreDiaLcd[diaDeLaSemana]);
  lcd.print(" ");
  lcd.print(dia);
  lcd.print(" ");
  lcd.print(nombreMesLcd[mes - 1]);
  lcd.print(" ");
  lcd.print(anio);



  lcd.setCursor(0, 1);
  if (hora < 10) {
    lcd.setCursor(0, 1);
    lcd.print("0");
  }
  lcd.print(hora);
  lcd.print(":");
  lcd.setCursor(3, 1);


  if (minuto < 10) {
    lcd.setCursor(3, 1);
    lcd.print("0");
  }

  lcd.print(minuto);
  lcd.print(":");


  lcd.setCursor(6, 1);
  if (segundo < 10) {
    lcd.setCursor(6, 1);
    lcd.print("0");
  }
  lcd.print(segundo);
  // lcd.print("\xDF") ; //imprime el simbolo de grados
}

//---------------------------------
void rele(int t = 1) {  // REVISAR LA LOGICA PARA NO USAR DELAY EN EL RELE


  int tiempoRele = t * 1000;

  digitalWrite(relePin, 1);
  delay(tiempoRele);
  digitalWrite(relePin, 0);
}
//-------------------------------
void revisarRTC() {
  rtc.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la FechaHora y hora (Comentar una vez establecida la hora)

  if (!rtc.begin()) {
    Serial.println("ERROR CON EL RTC");
    lcd.print("ERROR CON EL RTC");
    Serial.flush();
    while (1) delay(10);
  }
  //-------------------------------
  leerFechaHora(leerFechaModoManual);
  if ((FechaHora.unixtime() < FechaCero)) {
    Serial.println("ERROR CON LA BATERIA REVISAR LA FECHA");
    //beep(3);
    // Beeps.evaluar(3);// CAMBIAR AQUI
    lcd.setCursor(0, 0);
    lcd.print("FECHA ERROR");
    delay(5000);
    //beep(3);
    //Beeps.evaluar(3);//CAMBIAR AQUI
    HoraLcd();
    lcd.setCursor(10, 1);
    lcd.print("ERROR");


    while (((FechaHora.unixtime() < FechaCero))) delay(100);
  }
}
//---------------------------------
void iniciarLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void HoraSr() {

  leerFechaHora(leerFechaModoManual);


  segundo = FechaHora.second();
  minuto = FechaHora.minute();
  hora = FechaHora.hour();
  dia = FechaHora.day();
  mes = FechaHora.month();
  anio = FechaHora.year();
  diaDeLaSemana = FechaHora.dayOfTheWeek();
  //-------------------------------



  data = "";

  if (hora < 10) {

    data = "0";
  }
  data = data + hora;
  // Serial.print(seg_ant);
  // Serial.print(" ");
  // Serial.println(segundo);

  if (seg_ant != segundo) {
    seg_ant = segundo;
    seg_on = !seg_on;
  }

  if (seg_on) {
    data = data + "";

  } else {
    data = data + ".";
  }



  if (minuto < 10) {
    data = data + "0";
  }

  data = data + minuto;
  if (seg_on) {
    data = data + ".";

  } else {
    data = data + "";
  }
  sr.print(&data);
}




//---------------------------------