#include <DHT.h>
#include <LiquidCrystal.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
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
#define DHTTYPE DHT11

#define BLINKDELAY 200
#define DBDELAY 200
#define RUN_INTERVAL_SAVEDB 30000 //in ms

short HIGHTEMPERATURE=30; 
short LOWTEMPERATURE=20; 
short HIGHHUMIDITY=80; 
short LOWHUMIDITY=10;
String sketche_version = "0.2";
float temperature = 0;
float humidity = 0;
YunServer server;

unsigned long lastRun = (unsigned long)-60000;
DHT dht(DHT11_PIN, DHTTYPE);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
char* dbPath = "/tmp/temp_sensor.db";

void setup() {
  pinMode(13, OUTPUT);  
  digitalWrite(13, HIGH);
  Bridge.begin();
  if(!Serial)
    Serial.begin(9600);
  lcd.begin(16, 2);
  sendDBCommand(String("DROP TABLE sensor"));
  delay(DBDELAY);
  sendDBCommand(String("CREATE TABLE sensor (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp DATE DEFAULT CURRENT_TIMESTAMP, temp REAL NOT NULL, humidity REAL NOT NULL);"));
  initiateScripts();
  server.begin();
  digitalWrite(13, LOW);
}

void loop() {
  YunClient client = server.accept();
  if (client) {
    processClient(client);
    client.stop();
  }
  delay(50);
   
  unsigned long now = millis();
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)){
    DEBUG_PRINTLN(F("There was an error with the sensor."));
    writeInLcd("Sensor error", "Check pin");
    blinkScreen();
  }else{
    if ((humidity < LOWHUMIDITY) || (humidity > HIGHHUMIDITY) || (temperature < LOWTEMPERATURE) || (temperature > HIGHTEMPERATURE)){
      DEBUG_PRINTLN(F("Abnormal values detected."));
      blinkScreen();
    }
    char temp[20] = "";
    char hum[20] = "";
    formatValues(temperature, humidity, temp, hum);
    writeInLcd(temp, hum);
    if (now - lastRun >= RUN_INTERVAL_SAVEDB) {
      char t[6]=""; // Buffer big enough for 5-character float
      char h[6]=""; // Buffer big enough for 5-character float
      dtostrf(temperature, 3, 2, t);
      dtostrf(humidity, 3, 2, h);
      sendDBCommand(String("INSERT INTO sensor (temp, humidity) VALUES (")+String(t)+", "+String(h)+String(");"));
      DEBUG_PRINTLN(F("Saving in BD..."));
      lastRun = now;
    }
  }
}

//The two buffers parameters need to have at least 17 bytes of size.
char* formatValues(float temperature, float humidity, char* tempBuf, char* humBuf){
  char t[6]=""; // Buffer big enough for 5-character float
  char h[6]=""; // Buffer big enough for 5-character float
  dtostrf(temperature, 3, 0, t);
  dtostrf(humidity, 3, 0, h);
  strcpy(tempBuf, "Temperature");
  strcpy(humBuf, "Humidity");
  strcat(tempBuf, t);
  strcat(humBuf, h);
  strcat(tempBuf, "\xDF");
  strcat(tempBuf, "C");
  strcat(humBuf, "\x25");
}

void sendDBCommand(String command){
   Process proc;
   String cmd = "sqlite3 -line ";
   proc.runShellCommand(cmd+String(dbPath)+String(" '"+command+"'"));
}

void initiateScripts(){
   Process proc;
   proc.runShellCommand("chmod 777 -R /root/scripts/");
   proc.runShellCommand("/root/scripts/init_all.sh");
}

void blinkScreen(){
  for(int i=0; i<10; i++){
    lcd.noDisplay();
    delay(BLINKDELAY);
    lcd.display();
    delay(BLINKDELAY);
  }
}

void writeInLcd(char* firstLine, char* secondLine){
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}//TODO check msg size to scroll

void processClient(YunClient client) {
  client.setTimeout(200);
  String command = client.readStringUntil('/');
  command.trim();
  if (command == "temp" || command == "hum"){
    parameterCommand(client, command);
    return;
  }
  if (command == "version"){
    client.println(sketche_version);
    return;
  }
  client.println(F("Call not implemented"));
}

void parameterCommand(YunClient client, String parameter) {
  short value;
  String option = client.readStringUntil('/');//Read until /alta/
  option.trim();
  if (option != "") {//if something after temp or hum (alta or baja)
    String value = client.readStringUntil('/');
    if (value != ""){//if something after alta or baja (value)
      short new_value = value.toInt();
      if (option == "alta"){
        if(parameter == "temp"){
          HIGHTEMPERATURE = new_value;
          client.print(F("Established new high temperature threshold -> "));
        }else{
          client.print(F("Established new high humidity threshold -> "));
          HIGHHUMIDITY = new_value;
        }
      }
      if(option == "baja"){ //option is baja
        if(parameter == "temp"){
          LOWTEMPERATURE = new_value;
          client.print(F("Established new low temperature threshold -> "));
        }else{
          client.print(F("Established new low humidity threshold -> "));
          LOWHUMIDITY = new_value;
        }
      }
    client.println(value);
    }else{//If only goes until alta or baja
      if (option == "alta"){
        if(parameter == "temp")
          client.println(HIGHTEMPERATURE);
        else
          client.println(HIGHHUMIDITY);
      }
      if(option == "baja"){ //option is baja
        if(parameter == "temp")
          client.println(LOWTEMPERATURE);
        else
          client.println(LOWHUMIDITY); 
      }
    }
  }else{//Only goes until temp/hum
    client.print(F("Last reading -> "));
    if(parameter == "temp")
      client.println(temperature);
    else
      client.println(humidity);
  }
}

