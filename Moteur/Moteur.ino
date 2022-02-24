#include <IRremote.h>
#include <dht11.h>
#define DHT11PIN 9
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

const int dBack =2;
const int dFor =3;
const int gBack =4;
const int gFor =5;
const int DIN_ECHO = 6;
const int DOUT_TRIGGER = 7;
const int buzzer = 10;
float distance;
int Mode =0;
const int DIN_RECEPTEUR_INFRAROUGE = 8;
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);
decode_results messageRecu;
LiquidCrystal lcd(37,35,33,31,29,27);
RTC_DS3231 rtc;
dht11 DHT11;
char daysOfTheWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
char Months[13][12] = {"","Janv.", "Fev.", "Mars", "Avril", "Mai", "Juin", "Juil.","Aout", "Sept.", "Oct.", "Nov.", "Dec."};
int chrono =0;
int mLCD = 0;
int temp;
int hum;

void setup() {
  Serial.begin(9600);
  pinMode(dFor, OUTPUT);
  pinMode(dBack, OUTPUT);
  pinMode(gFor, OUTPUT);
  pinMode(gBack, OUTPUT);
  pinMode(DOUT_TRIGGER, OUTPUT);
  pinMode(DIN_ECHO, INPUT);
  monRecepteurInfraRouge.enableIRIn();
  monRecepteurInfraRouge.blink13(true);
  pinMode(buzzer, OUTPUT);
  rtc.begin();
  lcd.begin(16,2);
  lcd.clear();
}

void TestObstacle (){
  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER, LOW);
  distance = pulseIn(DIN_ECHO, HIGH) /58.0;
}

void Stop (){
  digitalWrite(dFor, LOW);  
  digitalWrite(dBack, LOW);
  digitalWrite(gFor, LOW);
  digitalWrite(gBack, LOW);
}

void Back (){
  digitalWrite(dFor, LOW);  
  digitalWrite(dBack, HIGH);
  digitalWrite(gFor, LOW);
  digitalWrite(gBack, HIGH);
}

void Right (){
  digitalWrite(dFor, LOW);  
  digitalWrite(dBack, HIGH);
  digitalWrite(gFor, HIGH);
  digitalWrite(gBack, LOW);
}

void Left (){
  digitalWrite(dFor, HIGH);  
  digitalWrite(dBack, LOW);
  digitalWrite(gFor, LOW);
  digitalWrite(gBack, HIGH);
}

void Esquive(){
  tone (buzzer, 440, 500);
  Back();
  delay(100);
  if (random(1,3)==1){
    Left ();
    delay(650);
  }
  if (random(1,3)==2){
    Right ();
    delay(650);
  }
}

void For (){
  TestObstacle();
  if (distance > 20.0){
    digitalWrite(dFor, HIGH);  
    digitalWrite(dBack, LOW);
    digitalWrite(gFor, HIGH);
    digitalWrite(gBack, LOW);
  }
  if (distance <= 20.0){
    Esquive();
  }
}

void Jour(){
  DateTime now = rtc.now();
  lcd.setCursor(2,0);
  lcd.print ("Nous sommes");
  lcd.setCursor(4,1);
  lcd.print (daysOfTheWeek[now.dayOfTheWeek()]);
}

void Heure(){
  DateTime now = rtc.now();
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
}

void CheckTemp(){
  DHT11.read(DHT11PIN);
  temp=(float)DHT11.temperature;
  hum=(float)DHT11.humidity;
}

void Temp(){
  lcd.setCursor(2,0);
  lcd.print("Il fait ");
  lcd.print((int)temp);
  lcd.print(" C");

  lcd.setCursor(1,1);
  lcd.print("Humidite: ");
  lcd.print((int)hum);
  lcd.print("%");
}

void loop() {
  if (monRecepteurInfraRouge.decode(&messageRecu)){
    // avant 
    if (messageRecu.value==0xC26BF044){
      For();
      Mode=1;
    }
    // arrière
    if (messageRecu.value==0xC4FFB646){
      Back();
      Mode=2;
    }
    // droite
    if (messageRecu.value==0x53801EE8){
      Right();
      delay(215);
      if(Mode==0){
        Stop();
      }
      if(Mode==1){
        For();
      }
      if(Mode==2){
        Back();
      }
    }
    // gauche
    if (messageRecu.value==0x758C9D82){
      Left();
      delay(215);
      if(Mode==0){
        Stop();
      }
      if(Mode==1){
        For();
      }
      if(Mode==2){
        Back();
      }
    }
    // STOP
    if (messageRecu.value==0x8AF13528){
      Stop();
      Mode=0;
    }
  delay(500);
  monRecepteurInfraRouge.resume();
  }

  if (chrono>=600){
    chrono = 0;
    lcd.clear();
    mLCD=mLCD+1;
    if(mLCD==2){
      CheckTemp();
    }
    if(mLCD==3){
      mLCD=0;
      Jour();
    }
  }

  if(Mode==0){
    Stop();
  }  
  if(Mode==1){
    For();
  }
  if(Mode==2){
    Back();
  }

  if(mLCD==0){
    Jour();
  }
  if(mLCD==1){
    Heure();
  }
  if(mLCD==2){
    Temp();
  }
  chrono = chrono+1;
  Serial.println(chrono);
}
