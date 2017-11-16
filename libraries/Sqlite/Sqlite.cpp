#include "Sqlite.h"

Sqlite::Sqlite(char* dbPath, int led_built_in){ 
  pinMode(led_built_in, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  path = dbPath;
  Bridge.begin();//TODO ask how to check if has begun already 
  if(!Serial){
    Serial.begin(9600);
    while (!Serial);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void Sqlite::sendCommand(char* command){
   Process p;
   String cmd = "sqlite3 -line ";
   String dbCommand = String(" '"+String(command)+"'");
   p.runShellCommand(cmd+String(path)+dbCommand);
   while (p.available()>0) {
     char c = p.read();
     DEBUG_PRINT(c);
   }
}