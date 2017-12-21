#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
YunServer server;
short high_temp=30; 
short low_temp=20; 
short high_hum=80; 
short low_hum=0;
float sketche_version = 0.1;
float last_temp = 20.4;
float last_hum = 10.5;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
   YunClient client = server.accept();
   if (client) {
     processClient(client);
     client.stop();
   }
   delay(50); 
}

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
          high_temp = new_value;
          client.print(F("Established new high temperature threshold -> "));
        }else{
          client.print(F("Established new high humidity threshold -> "));
          high_hum = new_value;
        }
      }
      if(option == "baja"){ //option is baja
        if(parameter == "temp"){
          low_temp = new_value;
          client.print(F("Established new low temperature threshold -> "));
        }else{
          client.print(F("Established new low humidity threshold -> "));
          low_hum = new_value;
        }
      }
    client.println(value);
    }else{//If only goes until alta or baja
      if (option == "alta"){
        if(parameter == "temp")
          client.println(high_temp);
        else
          client.println(high_hum);
      }
      if(option == "baja"){ //option is baja
        if(parameter == "temp")
          client.println(low_temp);
        else
          client.println(low_hum); 
      }
    }
  }else{//Only goes until temp/hum
    Serial.print(F("Last reading -> "));
    if(parameter == "temp")
      client.println(last_temp);
    else
      client.println(last_hum);
  }
}
