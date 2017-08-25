#include <image.h>
#include <source.h>
#include <stdlib.h>
Image * Source::GetOutput() {
    return &outImg;
}

char * Source::sourceName() {
    return name;
}

