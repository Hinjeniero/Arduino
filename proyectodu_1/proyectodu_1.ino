#include <Sqlite.h>
#include <dht.h>
#include <LiquidCrystal.h>
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define DHT11_PIN 9
#define readingDelay 100 //in miliseconds
int readingsCont = 0;
bool ok = true;
dht DHT;
Sqlite database();
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  checkModules();
  if(ok){
    lcd.print("Initializing...");
  }
}

void loop() {
  if(ok){
    if(readingsCont == 300){
      //TODO SAVE IN BD
      readingsCont = 0;
    }
    int chk = DHT.read11(DHT11_PIN);
    char temp[6]=""; // Buffer big enough for 5-character float
    char hum[6]=""; // Buffer big enough for 5-character float
    dtostrf(DHT.temperature, 3, 1, temp);
    dtostrf(DHT.humidity, 3, 1, hum);
    writeInLcd(temp, hum);
    readingsCont++;
    delay(readingDelay);
  }
}

void checkModules(){
  DHT.read11(DHT11_PIN);
  for(int i=0; i<5; i++){ //5 readings
    if(DHT.temperature < -512){
      ok = false;
      writeInLcd("No DHT sensor!","Check pin");
      break;
    }
    delay(readingDelay);
  }
}

void writeInLcd(char* firstLine, char* secondLine){
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}//TODO check msg size


