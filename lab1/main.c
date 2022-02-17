#include <stdio.h>
#include "funcdef.h"

int main() {
    char *input = "..\\images\\lena.pgm";
    char *output = "..\\output\\lena_averFilter_3.pgm";

    ChangeImage(input, output);

    return 0;
}

int ChangeImage(char *filename, char *outfilename) {
    Image *image;
    Image *outimage;

    image = ReadPNMImage(filename);
    outimage = AverFilter(image, 3);
    SavePNMImage(outimage, outfilename);

    return (0);
}