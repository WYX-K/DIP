/*
    Author: Kingsley
    ID: 1930026123
    Date: 2022/02/21
*/
#pragma once
#pragma once

#include "typedef.h"
#include "func.c"
/*
    Introduction: Read Image
    Input: Image Path
*/
Image *ReadPNMImage(char *);
/*
    Introduction: Create Image
    Input: 1. Image Path
           2. The comment of image
*/
Image *CreateNewImage(Image *, char *comment);
/*
    Introduction: Save Image
    Input: 1. Image Pointer
           2. Image Path
*/
void SavePNMImage(Image *, char *);
/*
    Introduction: The function of Image Median Filter
    Input: 1. Image Pointer
           2. Filter kernel
           3. Filter kernel
*/
Image *MidFilterImage(Image *image, int number1, int number2);
/*
    Introduction: The function of Image Average Filter
    Input: 1. Image Pointer
           2. Filter kernel
           3. Filter kernel
*/
Image *AverFilterImage(Image *, int number1, int number2);
/*
    Introduction: The function of Image Average Filter. Including create and saving Image.
    Input: 1. Image Pointer
           2. Filter kernel
           3. Filter kernel
*/
int AverFilter(char *, char *, int number1, int number2);
/*
    Introduction: The function of Image Median Filter. Including create and saving Image.
    Input: 1. Image Pointer
           2. Filter kernel
           3. Filter kernel
*/
int MidFilter(char *, char *, int number1, int number2);