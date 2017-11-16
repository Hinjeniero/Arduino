#include "Arduino.h"
#include "Morse.h"
const char humanAlphabet[37] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0','\0'};
const char* const morseAlphabet[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};

Morse::Morse(int _pin, int dotDelay, int dashDelay, int waitDelayBetweenSymbols, int spaceDelayBetweenWords)
{ 
  dot=dotDelay;
  dash=dashDelay;
  wait=waitDelayBetweenSymbols;
  pause=spaceDelayBetweenWords;
  pin = _pin;
  pinMode(pin, OUTPUT);
}


void Morse::morseToPin(char* morseSentence){
  int i=0;
  while(morseSentence[i] != '\0'){
    if (morseSentence[i] == '.'){
      digitalWrite(pin, HIGH);
      delay(dot);
      digitalWrite(pin, LOW);
      delay(wait);
    }
    if (morseSentence[i] == '-'){
      digitalWrite(pin, HIGH);
      delay(dash);
      digitalWrite(pin, LOW);
      delay(wait);
    }
    if (morseSentence[i] == ' ')
      delay(pause);
    i++;
  }
}

int Morse::getSizeCharArray(char* humanSentence){
  int sizeSentence=0;
  while(true){ //This loop gets the humanPhrase size, excluding the \0 ending char
    if(humanSentence[sizeSentence] == '\0')
      break;
    sizeSentence++;
  }
  return sizeSentence;
}

char* Morse::humanToMorse(char* humanSentence){
  int sizeSentence=getSizeCharArray(humanSentence);
  char buf[sizeSentence*5]="";
  int i;
  for (i=0; i<sizeSentence; i++){
    char c = humanSentence[i];
    if(c>= 'A' && c <= 'Z' )//Converting uppercase to lowercase
      c=c+32;
    char* morseChar = charToMorse(c);
    strcat(buf, morseChar);
  }
  return buf;
}

char* Morse::charToMorse(char humanChar){
  int i=0;
  if(humanChar==' ')//If its a space, return a space
    return " ";
  for(i=0; humanAlphabet[i] != '\0'; i++){
    if (humanChar == humanAlphabet[i])//If the human char has a traslation in morse
      return morseAlphabet[i]; //We send the index of the char to a method to get the traduction
  }
  return "?";//IF it doesn't exist in humanAlphabet
}