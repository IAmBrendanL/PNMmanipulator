#include <sink.h>
#include <filters.h>
#include <string>
#include <iostream>
#include <logging.h>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>

Filter::Filter() {
    outImg.setSource(this);
}

void Filter::Update() {
    // update input and then call update
    char msg[128];

    sprintf(msg,"%s: about to update input1", sourceName());
    Logger::LogEvent(msg);
    img->Update();
    sprintf(msg,"%s: done updating input1", sourceName());
    Logger::LogEvent(msg);
    if (img2 != NULL) {
        sprintf(msg,"%s: about to update input2", sourceName());
        Logger::LogEvent(msg);
        img2->Update();
        sprintf(msg,"%s: done updating input1", sourceName());
        Logger::LogEvent(msg);
    }

    sprintf(msg,"%s: about to execute", sourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", sourceName());
    Logger::LogEvent(msg);
}

void Filter::SetInput(Image *inImg) {
    img = inImg;
}

void Filter::SetInput2(Image *inImg) {
    img2 = inImg;
}

void Shrinker::Execute() {
    // set defaults and test for odd/even cases
    int h = img->getHeight();
    int w = img->getWidth();
    bool odd = false;
    if (w % 2 == 1) odd = true;
    // set outImg dementions
    h = h/2;
    w = w/2;
    outImg.setWidth(w);
    outImg.setHeight(h);
    outImg.setPixel(w*h);

    // copy data
    for(int i=0; i < h; i++) {
        for(int j=0; j < w; j++) {
            if (odd) outImg.setAPixel(i*w+j, *img->getAPixel((2*(2*i*w+j))+2*i));
            else outImg.setAPixel(i*w+j, *img->getAPixel(2*(2*i*w+j)));
        }
    }
}

void LRConcat::Execute() {
    try {
        // catch exceptions
        if (img == NULL || img2 == NULL) {
            char msg[1024];
            sprintf(msg, "%s at least one input is NULL", sourceName());
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        if (img->getHeight() != img2->getHeight()) {
            char msg[1024];
            sprintf(msg, "%s heights must match: %d, %d", sourceName(),
                    img->getHeight(), img2->getHeight());
            DataFlowException e(sourceName(), msg);
            throw e;
        }

        // set up output
        outImg.setWidth(img->getWidth()+img2->getWidth());
        outImg.setHeight(img->getHeight());
        outImg.setPixel(outImg.getWidth()*outImg.getHeight());

        // copy data from leftInput
        int h = outImg.getHeight();
        int w = img->getWidth();
        int oW = outImg.getWidth();
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixel(i*oW+j, *img->getAPixel(i*w+j));
            }
        }
        // copy data from rightinput
        int w2 = img2->getWidth();
        for(int i=0; i < h; i++) {
            for(int j=w; j < oW; j++) {
                outImg.setAPixel(i*oW+j, *img2->getAPixel(i*w2+j-w));
            }
        }
    } catch (DataFlowException e) {
        Logger::LogEvent(e.what());
        throw e;
    }
}

void TBConcat::Execute() {
    try {
        // catch exceptions
        if (img->getWidth() != img2->getWidth()) {
            char msg[1024];
            sprintf(msg, "%s widths must match: %d, %d", sourceName(),
                    img->getWidth(), img2->getWidth());
            DataFlowException e(sourceName(), msg);
            throw e;
        }

        // set up output
        int h = img->getHeight();
        int h2 = img2->getHeight();
        int oH = h + h2;
        int w = img->getWidth();
        outImg.setWidth(w);
        outImg.setHeight(oH);
        outImg.setPixel(w*oH);

        // copy data from left Input
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixel(i*w+j, *img->getAPixel(i*w+j));
            }
        }
        // copy data from right Input
        for(int i=h; i < oH; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixel(i*w+j, *img2->getAPixel((i-h)*w+j));
            }
        }
     } catch (DataFlowException e) {
        Logger::LogEvent(e.what());
        throw e;
    }
}

void Blender::SetFactor(double f) {
    fac = f;
}

void Blender::Execute() {
    try {
        // catch exceptions
        if (img == NULL || img2 == NULL) {
            char msg[1024];
            sprintf(msg, "%s at least one input is NULL", sourceName());
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        if (img->getHeight() != img2->getHeight()) {
            char msg[1024];
            sprintf(msg, "%s heights must match: %d, %d", sourceName(),
                    img->getHeight(), img2->getHeight());
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        if (img->getWidth() != img2->getWidth()) {
            char msg[1024];
            sprintf(msg, "%s widths must match: %d, %d", sourceName(),
                    img->getWidth(), img2->getWidth());
            DataFlowException e(sourceName(), msg);
            throw e;
        }

        // set up output
        outImg.setWidth(img->getWidth());
        outImg.setHeight(img->getHeight());
        outImg.setPixel(outImg.getWidth()*outImg.getHeight());

        // copy data from inputs
        int h = outImg.getHeight();
        int w = img->getWidth();
        int oW = outImg.getWidth();
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixelVal(i*oW+j,
                fac*img->getAPixelVal(i*w+j, "r")+(1-fac)*img2->getAPixelVal(i*w+j, "r"), "r");

                outImg.setAPixelVal(i*oW+j,
                fac*img->getAPixelVal(i*w+j, "g")+(1-fac)*img2->getAPixelVal(i*w+j, "g"), "g");

                outImg.setAPixelVal(i*oW+j,
                fac*img->getAPixelVal(i*w+j, "b")+(1-fac)*img2->getAPixelVal(i*w+j, "b"), "b");
            }
        }
    } catch (DataFlowException e) {
        Logger::LogEvent(e.what());
        throw e;
    }
}

void Subtract::Execute() {
    try {
        if (img == NULL || img2 == NULL) {
            char msg[1024];
            sprintf(msg, "%s at least one input is NULL", sourceName());
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        if (img->getHeight() != img2->getHeight()) {
            char msg[1024];
            sprintf(msg, "%s heights must match: %d, %d", sourceName(),
                    img->getHeight(), img2->getHeight());
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        if (img->getWidth() != img2->getWidth()) {
            char msg[1024];
            sprintf(msg, "%s widths must match: %d, %d", sourceName(),
                    img->getWidth(), img2->getWidth());
            DataFlowException e(sourceName(), msg);
            throw e;
        }

        // set up output
        outImg.setWidth(img->getWidth());
        outImg.setHeight(img->getHeight());
        outImg.setPixel(outImg.getWidth()*outImg.getHeight());

        // copy data from leftInput
        int h = outImg.getHeight();
        int w = img->getWidth();
        int oW = outImg.getWidth();
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixelVal(i*oW+j,
                std::max(0, (img->getAPixelVal(i*w+j, "r")-img2->getAPixelVal(i*w+j, "r"))), "r");

                outImg.setAPixelVal(i*oW+j,
                std::max(0, (img->getAPixelVal(i*w+j, "g")-img2->getAPixelVal(i*w+j, "g"))), "g");

                outImg.setAPixelVal(i*oW+j,
                std::max(0, (img->getAPixelVal(i*w+j, "b")-img2->getAPixelVal(i*w+j, "b"))), "b");
            }
        }
    } catch (DataFlowException e) {
        Logger::LogEvent(e.what());
        throw e;
    }
}

void Grayscale::Execute() {
    // set up output
    int h = img->getHeight();
    int w = img->getWidth();
    outImg.setWidth(w);
    outImg.setHeight(h);
    outImg.setPixel(w*h);

    // copy data from leftInput
    int oW = w;
    for(int i=0; i < h; i++) {
        for(int j=0; j < w; j++) {
            int color = (img->getAPixelVal(i*w+j, "r")/5) +
            (img->getAPixelVal(i*w+j, "g")/2) + (img->getAPixelVal(i*w+j, "b")/4);
            outImg.setAPixelVal(i*oW+j, color, "r");
            outImg.setAPixelVal(i*oW+j, color, "g");
            outImg.setAPixelVal(i*oW+j, color, "b");
        }
    }
}

unsigned char Blur::averageColors(int i, int j, int w, std::string channel) {
    // This method will return the color val to set a blured pixel to

    unsigned char outInt = (img->getAPixelVal((i-1)*w+(j-1), channel)/8) +
    (img->getAPixelVal((i)*w+(j-1), channel)/8) +
    (img->getAPixelVal((i+1)*w+(j-1), channel)/8) +
    (img->getAPixelVal((i-1)*w+j, channel)/8) +
    (img->getAPixelVal((i+1)*w+j, channel)/8) +
    (img->getAPixelVal((i-1)*w+(j+1), channel)/8) +
    (img->getAPixelVal(i*w+(j+1), channel)/8) +
    (img->getAPixelVal((i+1)*w+(j+1), channel)/8);

    return outInt;
}

void Blur::Execute() {
    // set up output
    int h = img->getHeight();
    int w = img->getWidth();
    outImg.setWidth(w);
    outImg.setHeight(h);
    outImg.setPixel(w*h);

    // average images and blur
    int oW = w;
    for(int i=0; i < h; i++) {
        for(int j=0; j < w; j++) {
            if (i==0 || i==h-1 || j==0 || j==w-1) {
                outImg.setAPixelVal(i*oW+j, img->getAPixelVal(i*w+j, "r"), "r");
                outImg.setAPixelVal(i*oW+j, img->getAPixelVal(i*w+j, "g"), "g");
                outImg.setAPixelVal(i*oW+j, img->getAPixelVal(i*w+j, "b"), "b");
            } else {
                outImg.setAPixelVal(i*oW+j, averageColors(i,j,w,"r"), "r");
                outImg.setAPixelVal(i*oW+j, averageColors(i,j,w,"g"), "g");
                outImg.setAPixelVal(i*oW+j, averageColors(i,j,w,"b"), "b");
            }
        }
    }
}

void Rotate::Execute() {
    // set up output
    int h = img->getHeight();
    int w = img->getWidth();
    outImg.setWidth(h);
    outImg.setHeight(w);
    outImg.setPixel(w*h);

    // average images and blur
    int oW = h;
    int oH = w;
    for(int i=0; i < oH; i++) {
        for(int j=0; j < oW; j++) {
            outImg.setAPixelVal(i*oW+j, img->getAPixelVal((h-j-1)*w+i,"r"), "r");
            outImg.setAPixelVal(i*oW+j, img->getAPixelVal((h-j-1)*w+i,"g"), "g");
            outImg.setAPixelVal(i*oW+j, img->getAPixelVal((h-j-1)*w+i,"b"), "b");
        }
    }
}

void Mirror::Execute() {
    // set up output
    int h = img->getHeight();
    int w = img->getWidth();
    outImg.setWidth(w);
    outImg.setHeight(h);
    outImg.setPixel(w*h);

    // flip image
    for(int i=0; i < h; i++) {
        for(int j=0; j < w; j++) {
            outImg.setAPixelVal(i*w+j, img->getAPixelVal(i*w+(w-j), "r"),"r");
            outImg.setAPixelVal(i*w+j, img->getAPixelVal(i*w+(w-j), "g"),"g");
            outImg.setAPixelVal(i*w+j, img->getAPixelVal(i*w+(w-j), "b"),"b");
        }
    }
}

Color::Color(int inW, int inH, int inR, int inG, int inB) {
    strcpy(name, "Color");
    w = inW;
    h = inH;
    r = inR;
    g = inG;
    b = inB;
    outImg.setSource(this);

   }

void Color::Execute() {
    try {
        if (b > 255 || b < 0) {
            char msg[1024];
            sprintf(msg, "%s, colors must be be in range 0, 255: %d, %d, %d", sourceName(),
                    r,g,b);
            DataFlowException e(sourceName(), msg);
            throw e;
        }
        // set up output
        outImg.setWidth(w);
        outImg.setHeight(h);
        outImg.setPixel(w*h);

        // average images and blur
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                outImg.setAPixelVal(i*w+j, r, "r");
                outImg.setAPixelVal(i*w+j, g, "g");
                outImg.setAPixelVal(i*w+j, b, "b");
            }
        }
    } catch (DataFlowException e) {
        std::cerr<<"Here"<<std::endl;
        throw e;
    }
}

void CheckSum::OutputCheckSum(std::string filename) {
    // sums all of input image and outputs results to a file
    int h = img->getHeight();
    int w = img->getWidth();
    int rSum = 0;
    int gSum = 0;
    int bSum = 0;
    FILE *outFile = fopen(filename.c_str(), "w");

    // average images and blur
    for(int i=0; i < h; i++) {
        for(int j=0; j < w; j++) {
            rSum += img->getAPixelVal(i*w+j, "r");
            gSum += img->getAPixelVal(i*w+j, "g");
            bSum += img->getAPixelVal(i*w+j, "b");
        }
    }
    // here output the sums % 256 to a file
    fprintf(outFile, "CHECKSUM: %d, %d, %d\n", rSum % 256, gSum % 256, bSum % 256);

    // close file
    fclose(outFile);
}
