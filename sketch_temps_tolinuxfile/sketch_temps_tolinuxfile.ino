#include <Process.h>
#include "dht.h"
#define DHT11_PIN 7
#define maxsizedatebuf 30
#define maxsizebuf 50
dht DHT;

void setup() {
  // put your setup code here, to run once:
   Bridge.begin();
   Serial.begin(9600);
   while (!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  String date = String(runDate());
  int chk = DHT.read11(DHT11_PIN);
  String temp = String(DHT.temperature);
  String humid = String(DHT.humidity);
  date = String(date+","+temp+"ºC,"+humid+"% Humidity");
  char charBuf[maxsizebuf];
  date.toCharArray(charBuf, maxsizebuf);
  runEcho(charBuf, "/tmp/DHT11/sensor.log");
  delay(1000);
}

char* runDate(){
   char date[maxsizedatebuf] = "";
   Process p;
   p.begin("date");
   p.addParameter("+%y/%m/%d--%H:%M:%S");
   p.run();
   int i = 0;
   while (p.available()>0) {
     char c = p.read();
     date[i] = c;
     i+=1;
   }
   date[i-1]=0;//We don't want the \n
   return date;
}
void runEcho(char* lineToWrite, char* filePath){
   Serial.println(lineToWrite);
   Process p;
   char command[5+maxsizebuf+22]="echo ";
   strcat(command, lineToWrite);
   strcat(command, " >> ");
   strcat(command, filePath);
   p.runShellCommand(command);
}

