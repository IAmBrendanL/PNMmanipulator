#include <sink.h>
#include <string>
#ifndef PNMWRITER_H
#define PNMWRITER_H
class PNMwriter: public Sink {
  public:
    void Write(char *); 
};
#endif
