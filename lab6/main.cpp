/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-30 10:50:18
 * @Description: file content
 * @FilePath: \lab\lab2\main.c
 */
#include <stdio.h>

#include "funcdef.h"
#include "proto.h"

int main() {
    Image *image;
    Image *outimage;
    char *input, *output;
    /*
     *
     * lena.pgm
     *
     */
    input = (char *)"..\\images\\test.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\test_FFT.pgm";
    outimage = FFTImage(image);
    SavePNMImage(outimage, output);

    return 0;
}
