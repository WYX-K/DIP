/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-22 18:54:13
 * @LastEditTime: 2022-03-08 22:00:39
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

    output = "..\\output\\lena_Translation.pgm";
    outimage = TranslationImage(image, 100, 100);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_Rotation.pgm";
    outimage = RotationImage(image, 45);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_Shear.pgm";
    outimage = ShearImage(image, 1, 1);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_AverFilter_3_3.pgm";
    outimage = AverFilterImage(image, 3, 3);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_AverFilter_5_5.pgm";
    outimage = AverFilterImage(image, 5, 5);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_MidFilter_3_3.pgm";
    outimage = MidFilterImage(image, 3, 3);
    SavePNMImage(outimage, output);

    output = "..\\output\\lena_MidFilter_5_5.pgm";
    outimage = MidFilterImage(image, 5, 5);
    SavePNMImage(outimage, output);

    return 0;
}
