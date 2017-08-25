#include <string>
#ifndef IMAGE_H
#define IMAGE_H
// forward declaration
class Filter;
class PNMreader;
class Source;
typedef struct Pixel{
    unsigned char r,g,b;
} Pixel;


class Image{
  public:
    Image(); 
    Image(int w, int h);
    Image(int w, int h, Pixel *);
    Image(Image *img);
    ~Image();
    void Update();
    void setSource(Source *s);
    void setPixel(int size);
    void setAPixel(int location, Pixel inPixel);
    Pixel * getAPixel(int location);
    int getAPixelVal(int location, std::string color);
    void setAPixelVal(int location, int val, std::string color);
    void setWidth(int w);
    int getWidth();
    void setHeight(int h);
    int getHeight();
  private:
    Source *source = NULL;
    Image(Image &);
    int width, height;
    Pixel *pixel = NULL;

};
#endif
