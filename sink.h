#include <image.h>
#ifndef SINK_H
#define SINK_H
class Sink{
  public:
    void SetInput(Image *);
    void SetInput2(Image *);
  protected:
   Image *img = NULL;
   Image *img2 = NULL;
};
#endif
