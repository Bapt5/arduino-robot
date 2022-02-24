#include <dht11.h>
#define DHT11PIN 9 // broche DATA -> broche 9
 
dht11 DHT11;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("DHT11 programme d'essai ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}
 
void loop()
{
  DHT11.read(DHT11PIN);
 
  Serial.print("Humidité (%): ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("\t");
  Serial.print("Température (°C): ");
  Serial.println((float)DHT11.temperature, 2);
 
  delay(2000);
}
