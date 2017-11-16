#ifndef Morse_h
#define Morse_h

#include "Arduino.h"
class Morse
{
  public:
    Morse(int _pin, int dotDelay, int dashDelay, int waitDelayBetweenSymbols, int spaceDelayBetweenWords);
    void morseToPin(char* morseSentence);
    int getSizeCharArray(char* humanSentence);
    char* humanToMorse(char* humanSentence);
    char* charToMorse(char humanChar);
  private:
    int dot;
    int dash;
    int wait;
    int pause;
    int pin;
};

#endif