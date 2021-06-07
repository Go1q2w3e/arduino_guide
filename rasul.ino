#include "DHT.h"

#include <MHZ.h>

#include <RTC.h>

#include <Wire.h>

#define CO2_IN 3

#define DHTPIN 2

#define DHTTYPE DHT22

#define STATUS "status"

#define water_1_ON "w1on"

#define water_1_OFF "w1off"

#define check_water_1 10

#define check_water_2 11

#define water_1 4

#define LED_1_ON "l1on"

#define LED_1_OFF "l1off"

#define LED_2_ON "l2on"

#define LED_2_OFF "l2off"

#define LED_3_ON "l3on"

#define LED_3_OFF "l3off"

#define LED_1 6

#define LED_2 5

#define LED_3 7

#define delimeter "===================================================="

DHT dht(DHTPIN, DHTTYPE);

MHZ co2(CO2_IN, MHZ19B);

static DS3231 RTC;

void check_time()

{

Serial.print("Is Clock Running: ");

if (RTC.isRunning())

{

Serial.println("Yes");

Serial.print(RTC.getDay());

Serial.print("-");

Serial.print(RTC.getMonth());

Serial.print("-");

Serial.print(RTC.getYear());

Serial.print(" ");

Serial.print(RTC.getHours());

Serial.print(":");

Serial.print(RTC.getMinutes());

Serial.print(":");

Serial.print(RTC.getSeconds());

Serial.print("");

if (RTC.getHourMode() == CLOCK_H12)

{

switch (RTC.getMeridiem()) {

case HOUR_AM:

Serial.print(" AM");

break;

case HOUR_PM:

Serial.print(" PM");

break;

}

}

Serial.println("");

delay(1000);

}

else

{

delay(1500);

Serial.println("No");

Serial.println("Setting Time");

//RTC.setHourMode(CLOCK_H12);

RTC.setHourMode(CLOCK_H24);

RTC.setDateTime(__DATE__, __TIME__);

Serial.println("New Time Set");

Serial.print(__DATE__);

Serial.print(" ");

Serial.println(__TIME__);

RTC.startClock();

}

}

void Det_HT() {// Функция проверки темпиратуры и влажности

float h = dht.readHumidity();

float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {

Serial.println(F("Failed to read from DHT sensor!"));

return;

}

Serial.print(F("Humidity: "));

Serial.print(h);

Serial.print(F("% Temperature: "));

Serial.print(t);

Serial.println(F("°C "));

}

void Water_level_1() {

int i = digitalRead(check_water_1);

if (i == 0) {

Serial.println("Tank Full");

}

else {

Serial.println("Tank EMPTY");

}

}

void Water_level_2() {

int j = digitalRead(check_water_2);

if (j == 0) {

Serial.println("Tank Full");

}

else {

Serial.println("Tank EMPTY");

}

}

void check_CO2() {

int ppm_pwm = co2.readCO2PWM();

Serial.print("CO2: ");

Serial.print(ppm_pwm);

Serial.println(" pwm");

}

void check_user_command() {

if (Serial.available()) {

String strBuffer = Serial.readString();

if (strBuffer == STATUS) {

Serial.println(delimeter);

check_time();

Det_HT();

Water_level_1();

Water_level_2();

check_CO2();

}

else if (strBuffer == water_1_ON) {

digitalWrite(water_1, HIGH);

}

else if (strBuffer == water_1_OFF) {

digitalWrite(water_1, LOW);

}

else if (strBuffer == LED_1_ON) {

digitalWrite(LED_1, HIGH);

}

else if (strBuffer == LED_1_OFF) {

digitalWrite(LED_1, LOW);

}

else if (strBuffer == LED_2_ON) {

digitalWrite(LED_2, HIGH);

}

else if (strBuffer == LED_2_OFF) {

digitalWrite(LED_2, LOW);

}

else if (strBuffer == LED_3_ON) {

digitalWrite(LED_3, HIGH);

}

else if (strBuffer == LED_3_OFF) {

digitalWrite(LED_3, LOW);

}

}

}

void setup() {

RTC.begin();

dht.begin();

Serial.begin(9600);

pinMode(2, INPUT);

pinMode(10 , INPUT);

pinMode(11 , INPUT);

pinMode(delimeter, INPUT);

pinMode(CO2_IN, INPUT);

pinMode(check_time, INPUT);

pinMode(water_1, OUTPUT);

pinMode(water, INPUT);

pinMode(water, OUTPUT);

pinMode(LED_1, OUTPUT);

pinMode(LED_2, OUTPUT);

pinMode(LED_3, OUTPUT);

}

void loop() {

check_user_command() ;
