/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-31 19:35:20
 */
#include <stdio.h>

#include "funcdef.h"
#include "proto.h"

int main() {
    Image *image;
    Image *outimage;
    char *input, *output;

    input = (char *)"..\\images\\lena.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\lena_ILPF.pgm";
    outimage = ILPFImage(image, 10);
    SavePNMImage(outimage, output);

    return 0;
}
