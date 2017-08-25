#include <source.h>
#include <string>
#include <image.h>
#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader : public Source {
  public:
    PNMreader(char *name) ;
    virtual void Execute();
    virtual void Update();
  private:
    std::string filename;
};
#endif
