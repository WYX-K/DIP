#pragma once
#pragma once

#include "typedef.h"
#include "func.h"

void SavePNMImage(Image *, char *);
Image *AverFilter(Image *, int);
Image *ReadPNMImage(char *);
Image *CreateNewImage(Image *, char *comment);
int ChangeImage(char *, char *);
