#pragma once
#pragma once

#include "typedef.h"

void SavePNMImage(Image *, char *);
Image *SwapImage(Image *);
Image *ReadPNMImage(char *);
Image *CreateNewImage(Image *, char *comment);
int ChangeImage(char *, char *);
