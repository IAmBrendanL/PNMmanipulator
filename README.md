# PNMmanipulator
Manipulate PNM files in C++

This project is a uses C++ to manipulate P6 PNM files utilizing a demand-driven execution pipeline, logging, and exception handling.

The following operations can be performed:
  * Rotate 
  * Mirror 
  * Convert to Greyscale
  * Create an image of a specified color
  * Blur
  * Blend two images
  * Concatenate two images Left <-> Rright
  * Concatenate two images Top <-> Bottom
  * Shrink an image to quarter size
  * Subtract one image from another
  * Blend two images together
  
Funtionality is currently defined in the PNMmanipulator.C file and the input pnm is given as a command line argument. Currently, it is assumed that the PNM file is valid.

The following functionality is planned:
  * Verify that the input image is a valid file and has standard P6 PNM structure
  * Have Checksum only output on flag
  * Switch input to a text file which says which order to perform manipulations and which files to load
    
