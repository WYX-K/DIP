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

    // input = (char *)"..\\images\\large_septagon_gaussian_noise_mean_0_std_50_added.pgm";
    // image = ReadPNMImage(input);

    // outimage = OtusThresholdingImage(image);
    // output = (char *)"..\\output\\large_septagon_gaussian_noise_mean_0_std_50_added.pgm";
    // SavePNMImage(outimage, output);

    // outimage = AverFilterImage(image, 5, 5);
    // outimage = OtusThresholdingImage(outimage);
    // output = (char *)"..\\output\\large_septagon_gaussian_noise_mean_0_std_50_added_AverFilter_OtusThresholding.pgm";
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\septagon_noisy_shaded.pgm";
    // image = ReadPNMImage(input);

    // outimage = PartialOtusImage(image);
    // output = (char *)"..\\output\\septagon_noisy_shaded_partialOtusThresholding.pgm";
    // SavePNMImage(outimage, output);

    // outimage = OtusThresholdingImage(image);
    // output = (char *)"..\\output\\septagon_noisy_shaded_OtusThresholding.pgm";
    // SavePNMImage(outimage, output);

    // input = (char *)"..\\images\\spot_shaded_text_image.pgm";
    // image = ReadPNMImage(input);

    // outimage = MAverThresholdingImage(image);
    // output = (char *)"..\\output\\spot_shaded_text_image_MAver.pgm";
    // SavePNMImage(outimage, output);

    input = (char *)"..\\images\\defective_weld.pgm";
    image = ReadPNMImage(input);

    outimage = RGrowingImage(image);
    output = (char *)"..\\output\\defective_weld_rgrowing.pgm";
    SavePNMImage(outimage, output);

    return 0;
}