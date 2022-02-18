#pragma once
#pragma once

#include "typedef.h"

void SavePNMImage(Image *, char *);
Image *AverFilterImage(Image *, int number1, int number2);
Image *ReadPNMImage(char *);
Image *CreateNewImage(Image *, char *comment);
int AverFilter(char *, char *, int number1, int number2);
int MidFilter(char *, char *, int number1, int number2);
Image *MidFilterImage(Image *image, int number1, int number2);
int cmp(const void *a, const void *b);