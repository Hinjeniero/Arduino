#include "Sqlite.h"
Sqlite::Sqlite(char* dbPath, int led_built_in){ 
  pinMode(led_built_in, OUTPUT);
  digitalWrite(led_built_in, HIGH);
  path = dbPath;
  if(!Serial){
    Serial.begin(9600);
    while (!Serial);
  }
  Bridge.begin();
  digitalWrite(led_built_in, LOW);
}

void Sqlite::sendCommand(String command){
   String cmd = "sqlite3 -line ";
   String dbCommand = String(" '"+command+"'");
   proc.runShellCommand(cmd+String(path)+dbCommand);
   while (proc.available()>0) {
     char c = proc.read();
     Serial.print(c);
   }
}