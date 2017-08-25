#include <stdlib.h>
#include <image.h>
#include <string>
#include <sink.h>
#include <filters.h>
#include <PNMreader.h>
#include <iostream>
#include <source.h>


// constructors and destructors
Image::Image() {};
Image::Image(int w, int h) {
    width = w;
    height = h;
    pixel = new Pixel[width*height];
}
Image::Image(int w, int h, Pixel *pix) {
    width = w;
    height = h;
    pixel = pix;
}
Image::Image(Image *img) {
    width = img->width;
    height = img->height;
    pixel = new Pixel[width*height];
}

// methods
void Image::Update() {
   if (source != NULL) source->Update();
}

void Image::setSource(Source *s) {
    source = s;
}

// getters and setters
void Image::setPixel(int size) {
    if (pixel != NULL) delete pixel;
    pixel = new Pixel[width*height];
}
void Image::setAPixel(int location, Pixel inPixel) {
    pixel[location].r = inPixel.r;
    pixel[location].g = inPixel.g;
    pixel[location].b = inPixel.b;
}
int Image::getAPixelVal(int location, std::string color) {
    if (color.compare("r") == 0) {
        return pixel[location].r;
    }else if (color.compare("g") == 0) {
        return pixel[location].g;
    }else if (color.compare("b") == 0) {
        return pixel[location].b;
    }
}
void Image::setAPixelVal(int location, int val, std::string color) {
    if (color.compare("r") == 0) {
        pixel[location].r = val;
    }else if (color.compare("g") == 0) {
        pixel[location].g = val;
    }else if (color.compare("b") == 0) {
        pixel[location].b = val;
    }
}
Pixel * Image::getAPixel(int location) {
    return &pixel[location]; // this may or may not work
}
void Image::setWidth(int w) {
    width = w;
}
int Image::getWidth() {
    return width;
}
void Image::setHeight(int h) {
    height = h;
}
int Image::getHeight() {
    return height;
}

// destructor
Image::~Image() {
    if (pixel != NULL) {
        delete pixel;
    }
}
