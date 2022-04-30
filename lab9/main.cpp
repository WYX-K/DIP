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

    input = (char *)"..\\images\\headCT-Vandy.pgm";
    image = ReadPNMImage(input);

    outimage = LoGEdgeImage(image, 2.55);
    output = (char *)"..\\output\\headCT_Vandy_LoGEdge.pgm";
    SavePNMImage(outimage, output);

    outimage = CannyEdgeImage(image, 2.55);
    output = (char *)"..\\output\\headCT_Vandy_CannyEdge.pgm";
    SavePNMImage(outimage, output);

    outimage = RobertsGradientImage(image);
    output = (char *)"..\\output\\headCT_Vandy_Roberts.pgm";
    SavePNMImage(outimage, output);

    outimage = PrewittGradientImage(image);
    output = (char *)"..\\output\\headCT_Vandy_Prewitt.pgm";
    SavePNMImage(outimage, output);

    outimage = SobleGradientImage(image);
    output = (char *)"..\\output\\headCT_Vandy_Soble.pgm";
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\building_original.pgm";
    image = ReadPNMImage(input);

    outimage = RobertsGradientImage(image);
    output = (char *)"..\\output\\building_original_Roberts.pgm";
    SavePNMImage(outimage, output);

    outimage = PrewittGradientImage(image);
    output = (char *)"..\\output\\building_original_Prewitt.pgm";
    SavePNMImage(outimage, output);

    outimage = SobleGradientImage(image);
    output = (char *)"..\\output\\building_original_Soble.pgm";
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\noisy_fingerprint.pgm";
    image = ReadPNMImage(input);

    outimage = RobertsGradientImage(image);
    output = (char *)"..\\output\\noisy_fingerprint_Roberts.pgm";
    SavePNMImage(outimage, output);

    outimage = PrewittGradientImage(image);
    output = (char *)"..\\output\\noisy_fingerprint_Prewitt.pgm";
    SavePNMImage(outimage, output);

    outimage = SobleGradientImage(image);
    output = (char *)"..\\output\\noisy_fingerprint_Soble.pgm";
    SavePNMImage(outimage, output);

    outimage = LoGEdgeImage(image, 1.19);
    output = (char *)"..\\output\\noisy_fingerprint_LoGEdge.pgm";
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\noisy_fingerprint.pgm";
    image = ReadPNMImage(input);

    outimage = CannyEdgeImage(image, 1.19);
    output = (char *)"..\\output\\noisy_fingerprint_CannyEdge.pgm";
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\polymersomes.pgm";
    image = ReadPNMImage(input);

    outimage = GlobalThresholdingImage(image);
    output = (char *)"..\\output\\polymersomes_GT.pgm";
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\noisy_fingerprint.pgm";
    image = ReadPNMImage(input);

    outimage = GlobalThresholdingImage(image);
    output = (char *)"..\\output\\noisy_fingerprint_GT.pgm";
    SavePNMImage(outimage, output);

    return 0;
}