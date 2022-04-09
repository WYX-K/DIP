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
    // outimage = ZeroPadding(image);
    // outimage = HomomorphicImage(outimage, 20, 1, 0.5, 5);
    // outimage = RemoveZeros(outimage);
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\goldhill.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\goldhill_Homomorphic.pgm";
    // outimage = HomomorphicImage(image, 20, 4, 0.5, 5);
    // SavePNMImage(outimage, output);

    input = (char *)"..\\images\\Lena.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\Lena_Bandreject.pgm";
    outimage = ZeroPadding(image);
    outimage = AddSinNoiseImage(outimage, 5);
    outimage = BandrejectImage(outimage, 300, 50);
    outimage = RemoveZeros(outimage);
    SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\cameraWithNoise.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\cameraWithNoise_AdMedFilter.pgm";
    // outimage = AdMedFilterImage(image, 3, 9);
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\LenaWithNoise.pgm";
    // image = ReadPNMImage(input);

    // output = (char *)"..\\output\\LenaWithNoise_Bandreject.pgm";
    // image = ZeroPadding(image);
    // // image = FFTImage(image, 1);
    // image = BandrejectImage(image, 300, 50);
    // outimage = RemoveZeros(image);
    // SavePNMImage(outimage, output);

    // //    **********************************************************************

    // input = (char *)"..\\images\\lenaD1.pgm";
    // image = ReadPNMImage(input);

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
    // outimage = AlphaTrimmedMeanImage(image, 3, 3, 30);
    // SavePNMImage(outimage, output);

    // output = (char *)"..\\output\\lenaD1_AdMedFilter.pgm";
    // outimage = AdMedFilterImage(image, 3, 9);
    // SavePNMImage(outimage, output);

    return 0;
}