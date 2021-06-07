#include <SoftwareSerial.h> // берется из примера MH-Z19B в начале
#include <Wire.h> // берется из примера RTC DS3231 info
#include "DHT.h" // берется из примера DHTtester
#include "MHZ.h" // берется из примера MH-Z19B в начале
#include "RTC.h" // берется из примера RTC DS3231 info

//Переменная для углексилого газа
#define CO2_IN 11
//Переменные для датчика температуры и влажности
#define DHT22_PIN 10
#define DHTTYPE DHT22 // берется из примера DHTtester
//Переменныедля датчиков воды
#define WB_1_PIN 8
#define WB_2_PIN 9
//
#define WATER_POMP 4
//Переменные света
#define SVET_PIN_1 5
#define SVET_PIN_2 6
#define SVET_PIN_3 7

//Дополнительные свойства
MHZ co2(CO2_IN, MHZ19B); // берется из примера MH-Z19B в начале
DHT dht(DHT22_PIN, DHTTYPE); // берется из примера DHTtester
static DS3231 RTC; // берется из примера RTC DS3231 info

//Свои переменные
String a;
int b, StTime, FiTime;

const String waitg = "Command complete. What next?"; //Приветсвие

//Показывает углексилый газ
void CO2show()
{
Serial.println("CO2: " + String(co2.readCO2PWM())); // берется из примера MH-Z19B в части loop где ppm_pwm
}

//Показывает время
void Timeshow() //Берется из примера RTC DS3231 info (часть вывод дд.мм.гг, чч.мм.сс)
{
Serial.println(
"Date: " +
String(RTC.getDay()) + "." +
String(RTC.getMonth()) + "." +
String(RTC.getYear()) + "\n" + "Time: " +
String(RTC.getHours()) + ":" +
String(RTC.getMinutes()) + ":" +
String(RTC.getSeconds())
);
}


/*Влажность и температура берется из примера DHT tester в части
loop где объявляются переменные и выводятся на экран*/
//Показывает влажность
void Humishow()
{
Serial.println(
"Влажность: " +
String(dht.readHumidity()) + "%"
);
}

//Показывает температуру
void Tempshow()
{
Serial.println("Температура: " +
String(dht.readTemperature()) + "°C"
);
}

//Показывает наличие воды
void Vodashow() // Прописываешь сам
{
if (digitalRead(WB_1_PIN) == 0)
{
Serial.println("Вода есть");
}

else
{
Serial.println("Воды нет");
}
}

//Дальнейший код прописываешь сам

void WaterPomp_On()
{
digitalWrite(WATER_POMP, HIGH);
}

void WaterPomp_Off()
{
digitalWrite(WATER_POMP, LOW);
}
//Включить весь свет
void SvetAll_On()
{
digitalWrite(SVET_PIN_1, HIGH);
digitalWrite(SVET_PIN_2, HIGH);
digitalWrite(SVET_PIN_3, HIGH);
}

//Включить первую лампу
void Svet1_On()
{
digitalWrite(SVET_PIN_1, HIGH);
}

//Включить вторую лампу
void Svet2_On()
{
digitalWrite(SVET_PIN_2, HIGH);
}

//Включить третью лампу
void Svet3_On()
{
digitalWrite(SVET_PIN_3, HIGH);
}

//Выключить весь свет
void SvetAll_Off()
{
digitalWrite(SVET_PIN_1, LOW);
digitalWrite(SVET_PIN_2, LOW);
digitalWrite(SVET_PIN_3, LOW);
}

//Выключить первую лампу
void Svet1_Off()
{
digitalWrite(SVET_PIN_1, LOW);
}

//Выключить вторую лампу
void Svet2_Off()
{
digitalWrite(SVET_PIN_2, LOW);
}

//Выключить третью лампу
void Svet3_Off()
{
digitalWrite(SVET_PIN_3, LOW);
}

//Показывает всю статистику (время, углекислый газ, влажность, температуру и воду)
void Allshow()
{
Serial.println();
Timeshow();
delay(1000);
Serial.println();
CO2show();
delay(1000);
Serial.println();
Humishow();
delay(1000);
Serial.println();
Tempshow();
delay(2000);
Serial.println();
Vodashow();
delay(1000);
}

//Команды для пользователя
void user_commans()
{
while (Serial.available() > 0)
{
a = Serial.readString();

if (a == "1" || a == "All") //Команда, которая показывает статистику
{
Serial.print("\n");
Allshow();
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "2" || a == "Time" || a == "t") //Команды, которые показывают время
{
Serial.print("\n");
Timeshow();
delay(1000);
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "3" || a == "CO2") //Команды, которые показывают углекислый газ
{
Serial.print("\n");
CO2show();
delay(1000);
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "4" || a == "Humi") //Команды, которые показывают влажность воздуха
{
Serial.print("\n");
Humishow();
delay(1000);
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "5" || a == "Temp") //Команды, которые показывают температуру
{
Serial.print("\n");
Tempshow();
delay(1000);
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "6" || a == "Voda") //Команды, которые показывают наличие воды
{
Serial.print("\n");
Vodashow();
delay(1000);
Serial.print("\n");
Serial.println(waitg);
}

else if (a == "7+" || a == "SvetOn") //Команды, которые включает весь свет
{
SvetAll_On();
Serial.println("Свет вкл");
Serial.println(waitg);
}

else if (a == "7-" || a == "SvetOff") //Команды, которые выключает весь свет
{
SvetAll_Off();
Serial.println("Свет выкл");
Serial.println(waitg);
}

else if (a == "71+" || a == "SvetOn 1") //Команды, которые включает 1 свет
{
Svet1_On();
Serial.println("Свет 1 вкл");
Serial.println(waitg);
}

else if (a == "72+" || a == "SvetOn 2") //Команды, которые включает 2 свет
{
Svet2_On();
Serial.println("Свет 2 вкл");
Serial.println(waitg);
}

else if (a == "73+" || a == "SvetOn 3") //Команды, которые включает 3 свет
{
Svet3_On();
Serial.println("Свет 3 вкл");
Serial.println(waitg);
}

else if (a == "71-" || a == "SvetOff 1") //Команды, которые выключает 1 свет
{
Svet1_Off();
Serial.println("Свет 1 выкл");
Serial.println(waitg);
}

else if (a == "72-" || a == "SvetOff 2") //Команды, которые выключает 2 свет
{
Svet2_Off();
Serial.println("Свет 2 выкл");
Serial.println(waitg);
}

else if (a == "73-" || a == "SvetOff 3") //Команды, которые выключает 3 свет
{
Svet3_Off();
Serial.println("Свет 3 выкл");
Serial.println(waitg);
}
else if (a == "8+" || a == "WP_On")
{
WaterPomp_On();
Serial.println("Насос включён");
Serial.println(waitg);
}
else if (a == "8-" || a == "WP_Off")
{
WaterPomp_Off();
Serial.println("Насос выключён");
Serial.println(waitg);
}

else if (a == "ПоРж" || a == "wm")
{
if (b == 0)
{
Serial.println("Активен автоконтроль");
}

else
{
Serial.println("Активен ручной режим");
}

break;

}

// Переключение режима (Авт и Ручной)
else if (a == "AutOn")
{
b = 0;
Serial.println("Активирован автороконтоль");
}

else if (a == "ManOn")
{
b = 1;
Serial.println("Активирован ручной режим");
}

else
{
Serial.println("\n");
Serial.print("I don't know this command, MY LORD!");
Serial.println("\n");
}

}
}

void Light_Time() // Автоматическое вкл/выкл света
{
if (String(RTC.getHours()) > "05" && String(RTC.getHours()) < "18")
{
SvetAll_On();
}
else if (String(RTC.getHours()) > "17" && String(RTC.getHours()) < "06")
{
SvetAll_Off();
}
}

void Pomp_Time() // Автоматическое поливание вкл/выкл
{
if (String(String(RTC.getHours()) + ":" + String(RTC.getMinutes())) > "14:27" &&
String(String(RTC.getHours()) + ":" + String(RTC.getMinutes())) < "14:29")

{
WaterPomp_On();
}


else if (String(String(RTC.getHours()) + ":" + String(RTC.getMinutes())) > "14:28" ||
String(String(RTC.getHours()) + ":" + String(RTC.getMinutes())) < "14:27"
)

{
WaterPomp_Off();
}

// if (String(RTC.getHours()) > "13" && String(RTC.getMinutes()) > "50")

/* if (String(RTC.getHours()) > "14")
{
if (String(RTC.getMinutes()) > "0")
{
if (String(RTC.getSeconds()) > "0")
{
WaterPomp_On();
}

}
}
*/

// else if (String(RTC.getHours()) > "13" && String(RTC.getMinutes()) > "51")

/* else if (String(RTC.getHours()) > "14")
{
if (String(RTC.getMinutes()) > "0")
{
if (String(RTC.getSeconds()) > "10")
{
WaterPomp_On();
}

}
}

*/


}

void style_machine()
{
if (b == 0)
{
Light_Time();
Pomp_Time();
}

}

// БАЗОВЫЕ БЛОКИ

void setup()
{
Serial.begin(9600);
pinMode(CO2_IN, INPUT);
RTC.begin();
dht.begin();

pinMode(WATER_POMP, OUTPUT);
pinMode(SVET_PIN_1, OUTPUT);
pinMode(SVET_PIN_2,
OUTPUT);
pinMode(SVET_PIN_3, OUTPUT);
pinMode (10, INPUT);
pinMode (11, INPUT);

digitalWrite(WATER_POMP, LOW);
digitalWrite(SVET_PIN_1, LOW);
digitalWrite(SVET_PIN_2, LOW);
digitalWrite(SVET_PIN_3, LOW);
b = 0;

Serial.println("OK");
}

void loop()
{
user_commans();
delay(3000);

style_machine();
}
