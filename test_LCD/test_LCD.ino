 #include <LiquidCrystal.h>
 LiquidCrystal lcd(37,35,33,31,29,27);
void setup() {
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("mon ecran marche");
}
 
void loop() {
}
