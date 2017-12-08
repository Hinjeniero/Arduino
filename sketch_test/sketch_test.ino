#include <Process.h>
#include <Sqlite.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define pin_dht 9

//char* dbPath = "/tmp/temp_sensor.db";
//Sqlite dblibrary (dbPath, LED_BUILTIN);
/*DHT dht(pin_dht, DHTTYPE);

void setup() {
  if(!Serial){
    Serial.begin(9600);
    while (!Serial);
  }
  dht.begin();
  //dblibrary.sendCommand(String("DROP TABLE sensor"));
  //dblibrary.sendCommand(String("CREATE TABLE sensor (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp DATE DEFAULT CURRENT_TIMESTAMP, temp REAL NOT NULL, humidity REAL NOT NULL);"));
}

void loop() {
  // put your main code here, to run repeatedly:
  float caca = dht.readTemperature();
  float cipote = dht.readHumidity();
  Serial.println(caca);
  Serial.println(cipote);
  char t[6]=""; // Buffer big enough for 5-character float
  char h[6]=""; // Buffer big enough for 5-character float
  dtostrf(caca, 3, 1, t);
  dtostrf(cipote, 3, 1, h);
  //dblibrary.sendCommand(String("INSERT INTO sensor (temp, humidity) VALUES (")+String(t)+", "+String(h)+String(");"));
}*/
