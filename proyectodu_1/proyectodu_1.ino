#include <Sqlite.h>
#include <dht.h>
#include <LiquidCrystal.h>
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define DHT11_PIN 6
bool ok = true;
dht DHT;
Sqlite database();
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


void setup() {
  lcd.begin(16, 2);
  int chk = DHT.read11(DHT11_PIN);
  checkModules();
  if(ok){
    lcd.print("Initializing...");
  }
}

void loop() {
  if(ok){
    char temp[6]; // Buffer big enough for 5-character float
    char hum[6]; // Buffer big enough for 5-character float
    dtostrf(DHT.temperature, 4, 2, temp);
    dtostrf(DHT.humidity, 4, 2, hum);
    writeInLcd(temp, hum);
    delay(100);
  }
}

void checkModules(){
  float n;
  for(int i=0; i<5; i++){ //5 readings
    if(DHT.temperature < -512){
      ok = false;
      writeInLcd("No DHT sensor!","Check pin");
      break;
    }
    delay(100);
  }
}

void writeInLcd(char* firstLine, char* secondLine){
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}//TODO check msg size


