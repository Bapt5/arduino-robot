float distance;
const int DIN_ECHO = 38;
const int DOUT_TRIGGER = 40;

void setup() {
  Serial.begin(9600);
  pinMode(DOUT_TRIGGER, OUTPUT);
  pinMode(DIN_ECHO, INPUT);

}

void loop() {
  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds (2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds (10);
  digitalWrite(DOUT_TRIGGER, LOW);
  distance = pulseIn(DIN_ECHO, HIGH) /58.0;
  
  Serial.println(distance);
  delay (1000);

}
