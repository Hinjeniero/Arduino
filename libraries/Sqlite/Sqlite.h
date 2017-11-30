#ifndef Sqlite_h
#define Sqlite_h
#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif
#include <Process.h>

class Sqlite
{
  public:
    Sqlite(char* dbPath, int led_built_in);
    void sendCommand(String command);
  private:
    char path;
};
#endif