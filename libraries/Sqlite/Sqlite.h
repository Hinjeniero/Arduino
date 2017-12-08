#ifndef Sqlite_h
#define Sqlite_h
#include <Process.h>
class Sqlite
{
  public:
    Sqlite(char* dbPath, int led_built_in);
    void sendCommand(String command);
  private:
    char path;
    Process proc;
};
#endif