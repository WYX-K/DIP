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

    // input = (char *)"..\\images\\bridge.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\bridge_Homomorphic.pgm";
    // outimage = HomomorphicImage(image, 20, 1, 0.5, 5);
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\goldhill.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\goldhill_Homomorphic.pgm";
    // outimage = HomomorphicImage(image, 20, 1, 0.5, 5);
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\LenaWithNoise.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\LenaWithNoise_Bandreject.pgm";
    // outimage = BandrejectImage(image, 10, 100);
    // SavePNMImage(outimage, output);

    input = (char *)"..\\images\\lenaD1.pgm";
    image = ReadPNMImage(input);

    // output = (char *)"..\\output\\lenaD1_AverFilter.pgm";
    // outimage = AverFilterImage(image, 3, 3);
    // SavePNMImage(outimage, output);

    // output = (char *)"..\\output\\lenaD1_GeoFilter.pgm";
    // outimage = GeoFilterImage(image, 3, 3);
    // SavePNMImage(outimage, output);

    // output = (char *)"..\\output\\lenaD1_MidFilter.pgm";
    // outimage = MidFilterImage(image, 3, 3);
    // SavePNMImage(outimage, output);

    // output = (char *)"..\\output\\lenaD1_AlphaTrimmedMean.pgm";
    // outimage = AlphaTrimmedMeanImage(image, 3, 3, 3);
    // SavePNMImage(outimage, output);

    output = (char *)"..\\output\\lenaD1_AdMedFilter.pgm";
    outimage = AdMedFilterImage(image, 3, 3, 49);
    SavePNMImage(outimage, output);

    return 0;
}