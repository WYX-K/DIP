/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-29 19:56:02
 * @LastEditTime: 2022-03-31 16:05:04
 * @Description: file content
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <float.h>
static int NUM_y = 2, NUM_x = 2;

int cmp(const void *a, const void *b);
void fft_shift(struct _complex *src, int height, int width);
void split_array(struct _complex *src, struct _complex *dst, int x_n, int y_n, int flag, int height, int width);
void fft(struct _complex *src, struct _complex *dst, int flag, int height, int width);
Image *CreateNewImage(Image *, int height, int width, char *comment);
Image *Homomorphic(Image *image, float radius, float gamma1, float gamma2, float c);
unsigned char *Normal(double *arr_in, int size, int range);
double *getResult(struct _complex *src, int size);
#include "tools.cpp"