#include <dht.h>
#include <LiquidCrystal.h>
#include <Process.h>

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif

#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define DHT11_PIN 9
#define readingDelay 200 //in miliseconds //200 because with this library lower values give out a timeout error
#define highTemp 40
#define lowTemp 0
#define highHum 80
#define lowHum 20

int readingsCont = 0;
bool ok = true;
dht DHT;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  if(!Serial){
    Serial.begin(9600);
    while (!Serial);
  }
  lcd.begin(16, 2);
  sendCommand(String("DROP TABLE sensor"));
  sendCommand(String("CREATE TABLE sensor (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp DATE DEFAULT CURRENT_TIMESTAMP, temp REAL NOT NULL, humidity REAL NOT NULL);"));
}

void loop() {
  if(tempSensorIsOkay()){
    float temperature = DHT.temperature;
    float humidity = DHT.humidity;
    if ((humidity < lowHum) || (humidity > highHum) || (temperature < lowTemp) || (temperature > highTemp))
      blinkScreen();
    char t[6]=""; // Buffer big enough for 5-character float
    char h[6]=""; // Buffer big enough for 5-character float
    dtostrf(temperature, 3, 1, t);
    dtostrf(humidity, 3, 1, h);
    char temp[16]="Temperature "; // Buffer big enough for 5-character float temperature 49
    char hum[16]="Humidity ";
    strcat(temp, t);
    strcat(hum, h);
    writeInLcd(temp, hum);
    readingsCont++;
    if(readingsCont == 10){
      sendCommand(String("INSERT INTO sensor (temp, humidity) VALUES (")+String(t)+", "+String(h)+String(");"));
      DEBUG_PRINTLN("Saving in BD...");
      readingsCont = 0;
    }
    delay(readingDelay);
    Serial.println(readingsCont);
  }
}

bool tempSensorIsOkay(){
  int chk = DHT.read11(DHT11_PIN); //This refresh is enough to get the temps in the loop
  if(chk != 0){
    Serial.println(chk);
    DEBUG_PRINTLN("Error in values, this could be caused by a faulty pin or a timeout in the temp query (If you have an high refresh rate).");
    writeInLcd("Sensor is faulty!","Check pin");
    ok = false;
    return true;
  }else if(!ok && chk == 0){
    DEBUG_PRINTLN("Values back to normal");
    ok = true; 
  }
  return false;
}

void sendCommand(String command){
   Process p;
   String cmd = "sqlite3 -line ";
   String dbCommand = String(" '"+command+"'");
   Serial.println(cmd+String("/tmp/temp_sensor.db")+dbCommand);
   p.runShellCommand(cmd+String("/tmp/temp_sensor.db")+dbCommand);
   /*while (p.available()>0) {
     char c = p.read();
     Serial.print(c);
   }*/
}

void blinkScreen(){
  for(int i=0; i<10; i++){
    lcd.noDisplay();
    delay(readingDelay);
    lcd.display();
    delay(readingDelay);
  }
}

void writeInLcd(char* firstLine, char* secondLine){
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}//TODO check msg size to scroll

