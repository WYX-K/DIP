/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-18 14:22:34
 * @Description: file content
 * @FilePath: \lab\lab2\main.c
 */
#include <stdio.h>
#include "funcdef.h"

int main() {
    Image *image;
    Image *outimage;
    char *input, *output;
    /*
     *
     * lena.pgm
     *
     */
    input = "..\\images\\lena.pgm";
    image = ReadPNMImage(input);

    output = "..\\output\\lena_DFT.pgm";
    outimage = DFTImage(image);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_PhaseAngle.pgm";
    outimage = PhaseAngleImage(image);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_Magnitude.pgm";
    outimage = MagnitudeImage(image);
    SavePNMImage(outimage, output);

    input = "..\\images\\bridge.pgm";
    image = ReadPNMImage(input);

    output = "..\\output\\bridge_DFT.pgm";
    outimage = DFTImage(image);
    SavePNMImage(outimage, output);

    input = "..\\images\\rectangle.pgm";
    image = ReadPNMImage(input);

    output = "..\\output\\rectangle_DFT.pgm";
    outimage = DFTImage(image);
    SavePNMImage(outimage, output);

    return 0;
}
