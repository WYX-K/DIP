/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-08 14:42:43
 * @LastEditTime: 2022-03-31 16:05:30
 */

#pragma once

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "typedef.h"
#include "tools.h"

/**
 * @description: Use adaptive median filter to get the image
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @param {int} smax - the max size of filter size
 * @return {Image} Image Pointer
 */
Image *AdMedFilterImage(Image *image, int number1, int number2, int smax);

/**
 * @description: Use Alpha Trimmed Mean to get the image
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @param {int} d
 * @return {Image} Image Pointer
 */

Image *AlphaTrimmedMeanImage(Image *image, int number1, int number2, int d);

/**
 * @description: Use Geo Filter to get the image
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @return {Image} Image Pointer
 */
Image *GeoFilterImage(Image *image, int number1, int number2);

/**
 * @description: Use Bandreject to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} w - Bandwidth
 * @param {float} c - Cut-off frequency
 * @return {Image} Image Pointer
 */
Image *BandrejectImage(Image *image, float w, float c);

/**
 * @description: Use Homomorphic to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} radius - Cut-off frequency
 * @param {float} gamma1 - gamma1 of the filter
 * @param {float} gamma2 - gamma2 of the filter
 * @param {float} c - c of the filter
 * @return {Image} Image Pointer
 */
Image *HomomorphicImage(Image *image, float radius, float gamma1, float gamma2, float c);

/**
 * @description: Use BHPF_TImage to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} radius - Cut-off frequency
 * @param {float} rank - rank of the filter
 * @return {Image} Image Pointer
 */
Image *BHPF_TImage(Image *image, float radius, float rank);

/**
 * @description: Use GLPF to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} radius - Cut-off frequency
 * @return {Image} Image Pointer
 */
Image *GLPFImage(Image *image, float radius);

/**
 * @description: Use BLPF to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} radius - Cut-off frequency
 * @param {float} rank - rank of the filter
 * @return {Image} Image Pointer
 */
Image *BLPFImage(Image *image, float radius, float rank);

/**
 * @description: Use ILPF to get the image
 * @param {Image} *image - Image Pointer
 * @param {float} radius - Cut-off frequency
 * @return {Image} Image Pointer
 */
Image *ILPFImage(Image *image, float radius);

/**
 * @description: Use Magnitude to reconstruct the image
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *MagnitudeImage(Image *image);

/**
 * @description: Use phase angle to reconstruct the image
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *PhaseAngleImage(Image *image);

/**
 * @description: Use DFT
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *DFTImage(Image *image);

/**
 * @description: Use histogram enhancement to enhance the image locally
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Locally enhanced width
 * @param {int} number2 - Locally enhanced height
 * @return {Image} Image Pointer
 */
Image *HistogramEnhancementLocalImage(Image *image, int number1, int number2);

/**
 * @description: Use histogram enhancement to enhance the image globally
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *HistogramEnhancementGlobalImage(Image *image);

/**
 * @description: Use Gamma correction to correction the image
 * @param {Image} *image - Image Pointer
 * @param {float} *gamma - Gamma value
 * @return {Image} Image Pointer
 */
Image *GammaCorrectionImage(Image *image, float gamma);

/**
 * @description: Use Sobel method to sharpen the image
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *SobelImage(Image *image);

/**
 * @description: Use Laplacian method to sharpen the image
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *LaplacianImage(Image *image);

/**
 * @description: Shear Image
 * @param {Image} *image - Image Pointer
 * @param {float} number - shear number
 * @param {float} type - shear type(0: vertical; 1: horizontal)
 * @return {Image} Image Pointer
 */
Image *ShearImage(Image *image, int type, float number);

/**
 * @description: Rotation Image
 * @param {Image} *image - Image Pointer
 * @param {float} theta - roatation angle
 * @return {Image} Image Pointer
 */
Image *RotationImage(Image *image, float theta);

/**
 * @description: Rotation Image
 * @param {Image} *image - Image Pointer
 * @param {float} theta - roatation angle
 * @return {Image} Image Pointer
 */
Image *RotationImage(Image *image, float theta);

/**
 * @description: Translation Image
 * @param {Image} *image - Image Pointer
 * @param {int} x_number - x axis translation
 * @param {int} y_number - y axis translation
 * @return {Image} Image Pointer
 */
Image *TranslationImage(Image *image, int x_number, int y_number);

/**
 * @description: Negative Image
 * @param {Image} *image - Image Pointer
 * @return {Image} Image Pointer
 */
Image *NegativeImage(Image *image);

/**
 * @description: Resize Image - Bilinear interpolation
 * @param {Image} *image - Image Pointer
 * @param {float} number - Adjusted size
 * @return {Image} Image Pointer
 */
Image *BilinearInterpolationImage(Image *image, float number);

/**
 * @description: Resize Image - Nearest Neighbor Interpolation
 * @param {Image} *image - Image Pointer
 * @param {float} number - Adjusted size
 * @return {Image} Image Pointer
 */
Image *NearestNeighborImage(Image *image, float number);

/**
 * @description: Resize Image - Pixel Replication
 * @param {Image} *image - Image Pointer
 * @param {int} number - Adjusted size
 * @return {Image} Image Pointer
 */
Image *PixelReplicationImage(Image *image, float number);

/**
 * @description:
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Image Pointer
 * @param {int} number2 - Filter kernel
 * @return {Image} Image Pointer
 */
Image *MidFilterImage(Image *image, int number1, int number2);

/**
 * @description: The function of Image Average Filter
 * @param {Image} * Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @return {Image} Image Pointer
 */
Image *AverFilterImage(Image *, int number1, int number2);

/**
 * @description: The function of Image Average Filter
 * @param {Image} * Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @return {Image} Image Pointer
 */
Image *AverFilterImage(Image *, int number1, int number2);

#include "func.cpp"