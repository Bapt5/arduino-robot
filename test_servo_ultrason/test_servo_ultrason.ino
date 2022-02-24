#include <Servo.h>

Servo servoAvant;
float distanceM;
float distanceD;
float distanceG;
const int DIN_ECHO_M = 6;
const int DOUT_TRIGGER_M = 7;
 
void setup()
{
  Serial.begin(9600); 
  servoAvant.attach(11);
  servoAvant.write(90);
  pinMode(DOUT_TRIGGER_M, OUTPUT);
  pinMode(DIN_ECHO_M, INPUT);
}
 
void loop()
{
  Serial.print(distanceG);
  Serial.print("   ");
  Serial.print(distanceM);
  Serial.print("   ");
  Serial.print(distanceD);
  Serial.println();
  // test au centre 
  servoAvant.write(90);
  delay(100);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER_M, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  distanceM = pulseIn(DIN_ECHO_M, HIGH) /58.0;
  delay(1000);
  // test à droite 
  servoAvant.write(30);
  delay(100);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER_M, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  distanceD = pulseIn(DIN_ECHO_M, HIGH) /58.0;
  delay(1000);
  // test au centre 
  servoAvant.write(90);
  delay(100);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER_M, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  distanceM = pulseIn(DIN_ECHO_M, HIGH) /58.0;
  delay(1000);
  // test à gauche 
  servoAvant.write(150);
  delay(100);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER_M, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER_M, LOW);
  distanceG = pulseIn(DIN_ECHO_M, HIGH) /58.0;
  delay(1000);
}
