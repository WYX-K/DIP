/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-02-21 18:10:01
 * @LastEditTime: 2022-02-23 12:20:44
 * @Description: Lab2
 * @FilePath: \lab\lab2\funcdef.h
 */

#pragma once
#pragma once

#include "typedef.h"
/**
 * @description: Negative Image
 * @param {Image} *image - Image Pointer
 * @return {*} Image Pointer
 */
Image *NegativeImage(Image *image);

/**
 * @description: Resize Image - Bilinear interpolation
 * @param {Image} *image - Image Pointer
 * @param {float} number - Adjusted size
 * @return {*} Image Pointer
 */
Image *BilinearInterpolationImage(Image *image, float number);

/**
 * @description: Resize Image - Nearest Neighbor Interpolation
 * @param {Image} *image - Image Pointer
 * @param {float} number - Adjusted size
 * @return {*} Image Pointer
 */
Image *NearestNeighborImage(Image *image, float number);

/**
 * @description: Resize Image - Pixel Replication
 * @param {Image} *image - Image Pointer
 * @param {int} number - Adjusted size
 * @return {*} Image Pointer
 */
Image *PixelReplicationImage(Image *image, float number);

/**
 * @description:
 * @param {Image} *image - Image Pointer
 * @param {int} number1 - Image Pointer
 * @param {int} number2 - Filter kernel
 * @return {*} Image Pointer
 */
Image *MidFilterImage(Image *image, int number1, int number2);

/**
 * @description: The function of Image Average Filter
 * @param {Image} * Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @return {*} Image Pointer
 */
Image *AverFilterImage(Image *, int number1, int number2);

/**
 * @description: The function of Image Average Filter
 * @param {Image} * Image Pointer
 * @param {int} number1 - Filter kernel
 * @param {int} number2 - Filter kernel
 * @return {*} Image Pointer
 */
Image *AverFilterImage(Image *, int number1, int number2);

/**
 * @description: Read Image
 * @param {char} * Input Image Path
 * @return {*} Image Pointer
 */
Image *ReadPNMImage(char *);

/**
 * @description: Create Image
 * @param {Image} * Image Pointer
 * @param {char} *comment - The comment of image
 * @return {*} Image Pointer
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