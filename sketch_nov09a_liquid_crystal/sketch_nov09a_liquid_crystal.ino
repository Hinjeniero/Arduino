#import <LiquidCrystal.h>
#define RS 12
#define E 11
#define D3 5
#define D2 4
#define D1 3
#define D0 2
LiquidCrystal lcd = LiquidCrystal(RS,E,D3,D2,D1,D0);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.print("Hello World");
}
