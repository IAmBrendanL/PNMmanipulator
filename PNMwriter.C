#include <sink.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <PNMwriter.h>


// methods
void PNMwriter::Write(char *filename) {
   // write to file
   int w = img->getWidth(); 
   int h = img->getHeight();
   FILE  *outFile = fopen(filename,"w");
   fprintf(outFile, "P6\n");
   fprintf(outFile, "%d %d\n",w, h); 
   fprintf(outFile, "%d\n", 255);
   for (int i=0;i < w*h; i++) {
       fwrite(img->getAPixel(i), sizeof(Pixel), 1, outFile);

   }
   // close file
   fclose(outFile);
}

