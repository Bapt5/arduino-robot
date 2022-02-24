#include <dht11.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#define DHT11PIN 9 

LiquidCrystal lcd(37,35,33,31,29,27);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
char Months[13][12] = {"","Janv.", "Fev.", "Mars", "Avril", "Mai", "Juin", "Juil.","Aout", "Sept.", "Oct.", "Nov.", "Dec."};
dht11 DHT11;

void setup() { 
 rtc.begin();
 lcd.begin(16,2);
 lcd.clear();
}
void loop() { 
  DateTime now = rtc.now();
  DHT11.read(DHT11PIN);
  int temp=(float)DHT11.temperature;
  int hum=(float)DHT11.humidity;

  lcd.setCursor(2,0);
  lcd.print ("Nous sommes");
  lcd.setCursor(4,1);
  lcd.print (daysOfTheWeek[now.dayOfTheWeek()]);

  delay(4000); 
  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print(now.day());
  lcd.print(" ");
  lcd.print(Months[now.month()]);
  lcd.print(" ");
  lcd.print(now.year());
  lcd.setCursor(4,1);
  lcd.print(now.hour());
  lcd.print("h");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
 
  delay(4000); 
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("Il fait ");
  lcd.print((int)temp);
  lcd.print(" C");

  lcd.setCursor(1,1);
  lcd.print("Humidite: ");
  lcd.print((int)hum);
  lcd.print("%");

  delay(4000); 
  lcd.clear();
}
