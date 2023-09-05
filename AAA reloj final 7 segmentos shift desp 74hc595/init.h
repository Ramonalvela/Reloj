//impresion en Shift register 7 segmentos
#define Version "V12.4"
#define Saludo_inicial "HOLA"
#include <ShiftRegisterQ.h>
int delayPersonalizado = 300;
ShiftRegisterQ sr(7, 9, 8, 7, 4);
String data = "";
uint8_t seg_ant = 0;
bool seg_on = 0;

#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include "EasyBuzzer.h"

// Describir Pines conectados
#define buzzerPin 10  // define es una directiva de pre compliado que cambia el nombre en el codigo por el valor
#define relePin 11
LiquidCrystal_I2C lcd(0x27, 16, 2);

RTC_DS1307 rtc;
const char nombreDia[7][12] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
const char nombreMes[12][12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };
const char nombreDiaLcd[7][12] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };
const char nombreMesLcd[12][12] = { "Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic" };
int segundo, minuto, hora, dia, mes, diaDeLaSemana;
int DiaAnterior;
long anio;  //variable año
const unsigned long FechaCero = 1656702350;


bool releEstado = 0;
byte buzzerMode = 0;

DateTime FechaHora;

bool sonarHorasPunto = 1;             // 1 Sono cada vez que es una hora en punto    0 no Sono
bool sonarSemanaHorasPunto = 0;       // 1 Sono solo entre semana                    0 Sono tambien los fines de semana
bool sonarSoloLaboralHorasPunto = 1;  // 1 Sono solo en horario laboral              0 Sono las 24 horas
bool sono = 1;
#define tonoHzBeep 600         // la frecuencia en Hertz del tono. Por defecto en 600
bool leerFechaModoManual = 0;  //en cero lee el RTC y en 1 toma la variable fechaManual
DateTime fechaManual(2022, 7, 18, 7, 55, 30); //(2022, 7, 18, 7, 55, 30);
// ultimo ajuste de hora (2023, 3, 20, 2, 5, 0);
#define velocidadHoraManual 25  // 1000 es la cantidad de milis que se le suma a la hora inicial en modo manual
