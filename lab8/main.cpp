/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-31 19:35:20
 */
#include <stdio.h>

#include "funcdef.h"

int main() {
    Image *image;
    Image *outimage;
    char *input, *output;

    input = (char *)"..\\images\\noisy_fingerprint.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\noisy_fingerprint_dilation.pgm";
    outimage = DilationImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_fingerprint_erosion.pgm";
    outimage = ErosionImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_fingerprint_open.pgm";
    outimage = OpenImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_fingerprint_close.pgm";
    outimage = CloseImage(image);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\noisy_rectangle.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\noisy_rectangle_dilation.pgm";
    outimage = DilationImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_rectangle_erosion.pgm";
    outimage = ErosionImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_rectangle_open.pgm";
    outimage = OpenImage(image);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\noisy_rectangle_close.pgm";
    outimage = CloseImage(image);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\licoln.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\licoln_ExtractBoundaries.pgm";
    outimage = ExtractBoundariesImage(image);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\U.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\U_ExtractBoundaries.pgm";
    outimage = ExtractBoundariesImage(image);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\connected.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\count_connect_pixel.txt";
    CountConnPixel(image, output);
    // only could run one by one
    input = (char *)"..\\images\\bubbles_on_black_background.pgm";
    image = ReadPNMImage(input);

    // output = (char *)"..\\output\\bubbles_on_black_background_border.pgm";
    // outimage = ConnBorderImage(image);
    // SavePNMImage(outimage, output);

    // output = (char *)"..\\output\\bubbles_on_black_background_OverlapPart.pgm";
    // outimage = OverlapPartImage(image);
    // SavePNMImage(outimage, output);

    output = (char *)"..\\output\\bubbles_on_black_background_NotOverlapPart.pgm";
    outimage = NotOverlapPartImage(image);
    SavePNMImage(outimage, output);

    return 0;
}