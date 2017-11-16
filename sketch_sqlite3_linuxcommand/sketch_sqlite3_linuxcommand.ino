#include <Process.h>
#include "dht.h"
#define DHT11_PIN 7
dht DHT;
char* databasePath = "/tmp/DHT11/sensor.db";

void setup() {
  // put your setup code here, to run once:
   Bridge.begin();
   Serial.begin(9600);
   while (!Serial);
   sqlcommand(String("CREATE TABLE sensor (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp DATE DEFAULT CURRENT_TIMESTAMP, temp REAL NOT NULL, humidity REAL NOT NULL);"));
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read11(DHT11_PIN);
  String temp = String(DHT.temperature);
  String humid = String(DHT.humidity);
  sqlcommand("INSERT INTO sensor (temp, humidity) VALUES ("+String(temp)+", "+String(humid)+");");
  delay(1000);
}

void sqlcommand(String command){
   Process p;
   String cmd = "sqlite3 -line ";
   String dbPath = String(databasePath);
   String dbCommand = String(" '"+command+"'");
   p.runShellCommand(cmd+dbPath+dbCommand);
   while (p.available()>0) {
     char c = p.read();
     Serial.print(c);
   }
}
