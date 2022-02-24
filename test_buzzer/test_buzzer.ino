const int buzzer = 10;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
    tone (buzzer, 440, 500);
    delay(2000);
    tone (buzzer, 659,500);
}
