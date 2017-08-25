#include <exception>
#include <stdio.h>
#include <string.h>
#include <logging.h>
#include <iostream>

// DataFlowException class

DataFlowException::DataFlowException(const char *type, const char *error){
    char tempStr[1024];
    strcpy(tempStr, "Throwing exception: (");
    strcat(tempStr, type);
    strcat(tempStr, "): ");
    strcat(tempStr, type);
    strcat(tempStr, ": ");
    strcat(tempStr, error);
    strcpy(msg, tempStr);
}

// Logger Class

bool Logger::logOpened = false;

FILE * Logger::logger;

void Logger::openLogF(const char *fname) {
    logger = fopen(fname, "w");
    logOpened = true;
}

void Logger::LogEvent(const char *event) {
    if(!logOpened) openLogF("logFile");
    fprintf(logger,"%s\n",event);
}

void Logger::Finalize() {
   fclose(logger); 
}
