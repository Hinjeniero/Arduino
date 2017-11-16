#include <Process.h>
#include <Morse.h>
#define pin 13
#define dotDelay 100
#define dashDelay 350
#define waitDelayBetweenSymbols 250
#define spaceDelayBetweenWords 1000
Morse morse(pin, dotDelay, dashDelay, waitDelayBetweenSymbols, spaceDelayBetweenWords);

void setup() {
  // put your setup code here, to run once:
   Bridge.begin();
   Serial.begin(9600);
   while (!Serial);
   runCat();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void runCat() {
   Process p;
   p.begin("cat");
   p.addParameter("/tmp/morse/textoamorse.txt");
   p.run();
   if(p.available()>0){
     String buf;
     int siz=0;
     while(p.available()>0){
       char c = p.read();
       buf = String(buf+c);
       siz++;
     }
     char charBuf[siz];
     buf.toCharArray(charBuf, siz);
     Serial.println("Human phrase is: ");
     Serial.println(charBuf);
     char* morseBuf = morse.humanToMorse(charBuf);
     Serial.println("Translation in morse is (non ASCII chars are represented with ??): ");
     Serial.println(morseBuf);
     Serial.println("Sending to pin...");
     morse.morseToPin(morseBuf);
     Serial.println("All sent, exiting");
     Serial.flush();
   }
}
