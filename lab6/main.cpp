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

    output = (char *)"..\\output\\lena_BLPF.pgm";
    outimage = BLPFImage(image, 10, 3);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\lena_GLPF.pgm";
    outimage = GLPFImage(image, 10);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\camera.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\camera_ILPF.pgm";
    outimage = ILPFImage(image, 10);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\camera_BLPF.pgm";
    outimage = BLPFImage(image, 10, 3);
    SavePNMImage(outimage, output);

    output = (char *)"..\\output\\camera_GLPF.pgm";
    outimage = GLPFImage(image, 10);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\fingerprint1.pgm";
    image = ReadPNMImage(input);
    output = (char *)"..\\output\\fingerprint1_BHPF_T.pgm";
    outimage = BHPF_TImage(image, 25, 4);
    SavePNMImage(outimage, output);

    input = (char *)"..\\images\\fingerprint2.pgm";
    image = ReadPNMImage(input);
    output = (char *)"..\\output\\fingerprint2_BHPF_T.pgm";
    outimage = BHPF_TImage(image, 25, 4);

    SavePNMImage(outimage, output);

    return 0;
}
