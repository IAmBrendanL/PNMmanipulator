#include <source.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <PNMreader.h>
#include <iostream>
#include <logging.h>

// constructors
PNMreader::PNMreader(char *n) {
   filename = n;
   outImg.setSource(this);
   strcpy(name, "PNMreader");
}

// Methods
void PNMreader::Execute() {

   // open file
   FILE *inFile = fopen(filename.c_str(), "rb");
   char magicNum[128];
   int width, height, maxval;
   fscanf(inFile, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

   outImg.setWidth(width);
   outImg.setHeight(height);
   outImg.setPixel(width*height);
   Pixel *temPixel = new Pixel;
   for(int i=0; i < width*height; i++) {
       fread(temPixel, sizeof(Pixel), 1, inFile);
       outImg.setAPixel(i, *temPixel);
   }

   // close file 
   fclose(inFile);
   delete temPixel;
}

void PNMreader::Update() {
    char msg[128];
    sprintf(msg, "%s: about to execute", sourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", sourceName());
    Logger::LogEvent(msg);
}
