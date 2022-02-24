#include <Servo.h>
 
Servo servoAvant;
 
void setup()
{
  servoAvant.attach(11);
  servoAvant.write(90);
}
 
void loop()
{
  servoAvant.write(150);
  delay(1000);
  servoAvant.write(30);
  delay(1000);
 
}
