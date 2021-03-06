
#ifndef  LOGGING_H
#define  LOGGING_H

#include <exception>
#include <stdio.h>

using std::exception;


class DataFlowException : public exception
{
  public:
    DataFlowException(const char *type, const char *error);
    virtual const char  *what() const throw() { return msg; };

  protected:
    char msg[1024];
};


class Logger
{
  public:
    static void LogEvent(const char *event);
    static void Finalize();
    static void openLogF(const char *fname);

  private:
    static FILE *logger;
    static bool logOpened; 
}; 
#endif
