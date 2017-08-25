#include <image.h>
#ifndef SOURCE_H
#define SOURCE_H
class Source{
  public:
    virtual Image * GetOutput();
    virtual void Update() = 0;
    virtual char * sourceName();
  protected:
    virtual void Execute() = 0;
    Image outImg;
    char name[128];
};
#endif
