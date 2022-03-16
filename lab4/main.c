/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-15 22:53:53
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
    printf("\n");

    output = "..\\output\\lena_Laplacian.pgm";
    outimage = LaplacianImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\lena_Sobel.pgm";
    outimage = SobelImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\lena_GammaCorrect_0.1.pgm";
    outimage = GammaCorrectionImage(image, 0.1);
    SavePNMImage(outimage, output);
    printf("\n");
    output = "..\\output\\lena_GammaCorrect_0.4.pgm";
    outimage = GammaCorrectionImage(image, 0.4);
    SavePNMImage(outimage, output);

    printf("\n");
    output = "..\\output\\lena_GammaCorrect_0.7.pgm";
    outimage = GammaCorrectionImage(image, 0.7);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\lena_GammaCorrect_1.pgm";
    outimage = GammaCorrectionImage(image, 1);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\lena_HistogramEnhancementGlobal.pgm";
    outimage = HistogramEnhancementGlobalImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\lena_HistogramEnhancementLocal.pgm";
    outimage = HistogramEnhancementLocalImage(image, 3, 3);
    SavePNMImage(outimage, output);
    printf("\n");

    /*
     *
     * bridge.pgm
     *
     */
    input = "..\\images\\bridge.pgm";
    image = ReadPNMImage(input);
    printf("\n");

    output = "..\\output\\bridge_Laplacian.pgm";
    outimage = LaplacianImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\bridge_Sobel.pgm";
    outimage = SobelImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\bridge_GammaCorrect_0.1.pgm";
    outimage = GammaCorrectionImage(image, 0.1);
    SavePNMImage(outimage, output);
    printf("\n");
    output = "..\\output\\bridge_GammaCorrect_0.4.pgm";
    outimage = GammaCorrectionImage(image, 0.4);
    SavePNMImage(outimage, output);

    printf("\n");
    output = "..\\output\\bridge_GammaCorrect_0.7.pgm";
    outimage = GammaCorrectionImage(image, 0.7);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\bridge_GammaCorrect_1.pgm";
    outimage = GammaCorrectionImage(image, 1);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\bridge_HistogramEnhancementGlobal.pgm";
    outimage = HistogramEnhancementGlobalImage(image);
    SavePNMImage(outimage, output);
    printf("\n");

    output = "..\\output\\bridge_HistogramEnhancementLocal.pgm";
    outimage = HistogramEnhancementLocalImage(image, 3, 3);
    SavePNMImage(outimage, output);
    printf("\n");

    return 0;
}
