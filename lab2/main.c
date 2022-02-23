/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-02-23 12:12:14
 * @Description: file content
 * @FilePath: \lab\lab2\main.c
 */
#include <stdio.h>
#include "funcdef.h"

int main() {
    Image *image;
    Image *outimage;
    /*
     *
     * lena.pgm
     *
     */
    char *input1 = "..\\images\\lena.pgm";
    image = ReadPNMImage(input1);

    char *output1 = "..\\output\\lena_PixelReplication.pgm";
    outimage = PixelReplication(image, 0.5);
    SavePNMImage(outimage, output1);

    char *output2 = "..\\output\\lena_NearestNeighbor.pgm";
    outimage = NearestNeighborImage(image, 2);
    SavePNMImage(outimage, output2);

    char *output3 = "..\\output\\lena_BilinearInterpolation.pgm";
    outimage = BilinearInterpolationImage(image, 2);
    SavePNMImage(outimage, output3);

    char *output4 = "..\\output\\lena_Negative.pgm";
    outimage = NegativeImage(image);
    SavePNMImage(outimage, output4);
    /*
     *
     * bridge.pgm
     *
     */
    char *input2 = "..\\images\\bridge.pgm";
    image = ReadPNMImage(input2);

    char *output5 = "..\\output\\bridge_PixelReplication.pgm";
    outimage = PixelReplication(image, 0.7);
    SavePNMImage(outimage, output5);

    char *output6 = "..\\output\\bridge_NearestNeighbor.pgm";
    outimage = NearestNeighborImage(image, 1.3);
    SavePNMImage(outimage, output6);

    char *output7 = "..\\output\\bridge_BilinearInterpolation.pgm";
    outimage = BilinearInterpolationImage(image, 2.5);
    SavePNMImage(outimage, output7);

    char *output8 = "..\\output\\bridge_Negative.pgm";
    outimage = NegativeImage(image);
    SavePNMImage(outimage, output8);

    return 0;
}
