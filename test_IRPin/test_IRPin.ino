#include <IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE = 8;

IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;

void setup()
{
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn();
 monRecepteurInfraRouge.blink13(true);
}

void loop()
{
  if (monRecepteurInfraRouge.decode(&messageRecu))
  {
    Serial.println(messageRecu.value,HEX);
    delay(500);
    monRecepteurInfraRouge.resume();
  }
  delay(1);
}
