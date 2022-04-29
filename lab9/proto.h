/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-29 20:03:54
 * @LastEditTime: 2022-03-29 21:00:49
 * @Description: file content
 */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "typedef.h"

/**
 * @description: Read Image
 * @param {char} * Input Image Path
 * @return {Image} Image Pointer
 */
Image *ReadPNMImage(char *);

/**
 * @description: Save Image
 * @param {Image} * Image Pointer
 * @param {char} * Image Path
 * @return {*}
 */
void SavePNMImage(Image *, char *);

#include "proto.cpp"