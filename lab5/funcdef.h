/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-08 14:42:43
 * @LastEditTime: 2022-03-18 13:10:09
 */

#pragma once
#pragma once

#include "typedef.h"

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

/**
 * @description: Read Image
 * @param {char} * Input Image Path
 * @return {Image} Image Pointer
 */
Image *ReadPNMImage(char *);

/**
 * @description: Create Image
 * @param {Image} * Image Pointer
 * @param {char} *comment - The comment of image
 * @return {Image} Image Pointer
 */
Image *CreateNewImage(Image *, int height, int width, char *comment);

/**
 * @description: Save Image
 * @param {Image} * Image Pointer
 * @param {char} * Image Path
 * @return {*}
 */
void SavePNMImage(Image *, char *);

#include "func.c"