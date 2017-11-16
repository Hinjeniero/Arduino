#include
#define DHT11_PIN 7
int count = 0;
//Serial.find() corrupted the serial port and it couldn't be read, so I don't have an end char or control.
//Also, the serial port restarts every 64 chars, so the maxSizeMsg always gives a false, even if the msg is larger.
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 while (!Serial) {
  ;
 } 
}

void loop() {
  // put your main code here, to run repeatedly:
  int numChars=0;
  if ((numChars=Serial.available()) > 0) {
    if(numChars > maxSizeMsg){
      Serial.println("Msg too long, try again.");
    }
    char bufer[numChars]="";
    for(int i=0; i<numChars; i++){ 
      bufer[i] = (char)Serial.read();
    }
    Serial.println(bufer);
    Morse morse(13);
    String morsePhrase = morse.humanToMorse(bufer, sizeof(bufer));
    Serial.println(morsePhrase);
    morse.morseToPin(morsePhrase);
  }
}



