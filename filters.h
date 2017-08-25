#include <source.h>
#include <sink.h>
#include <string.h>
#include <logging.h>
#ifndef FILTER_H
#define FILTER_H
class Filter: public Source, public Sink {
  public:
    virtual void SetInput(Image *);
    virtual void SetInput2(Image *);
    virtual void Update();
    Filter(); 
};

class Shrinker : public Filter {
  public:
    virtual void Execute();
    Shrinker() {strcpy(name,"Shrinker");};
};

class LRConcat : public Filter {
  public:
    virtual void Execute();
    LRConcat() {strcpy(name,"LRConcat");};
};

class TBConcat : public Filter {
  public:
    virtual void Execute();
    TBConcat() {strcpy(name,"TBConcat");};
};

class Blender: public Filter {
  public:
    virtual void Execute();
    void SetFactor(double f);
    Blender() {strcpy(name,"Blender");};
  private:
   double fac;
};

class Blur: public Filter {
  public:
    virtual void Execute();
    unsigned char averageColors(int i, int j, int w, std::string channel);
    Blur() {strcpy(name, "Blur");};
};

class Subtract: public Filter {
  public:
    virtual void Execute();
    Subtract() {strcpy(name, "Subtract");};
};

class Rotate: public Filter {
  public:
    virtual void Execute();
    Rotate() {strcpy(name, "Rotate");};
};

class Mirror: public Filter {
  public:
    virtual void Execute();
    Mirror() {strcpy(name, "Mirror");};
};

class Grayscale: public Filter {
  public:
    virtual void Execute();
    Grayscale() {strcpy(name, "Grayscale");};
};

class Color: public Source{
  public:
    Color(int w, int h, int r, int g, int b);
    virtual void Update() {Execute();};
    virtual void Execute();
  private:
    int w,h,r,g,b;
};

class CheckSum: public Sink {
  public:
    void OutputCheckSum(std::string);
};

#endif
