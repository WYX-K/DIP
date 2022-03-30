/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-29 19:56:02
 * @LastEditTime: 2022-03-30 11:17:14
 * @Description: file content
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <float.h>

int cmp(const void *a, const void *b);
unsigned char *Normal(int *arr_in, int size, int range);
unsigned char *Normal(double *arr_in, int size, int range);
void fft_shift(struct _complex *src, int height, int width);
void split_array(struct _complex *src, struct _complex *dst, int x_n, int y_n, int flag, int height, int width);
double *getResult(struct _complex *src, int size);
void fft(struct _complex *src, struct _complex *dst, int flag, int height, int width);

#include "tools.cpp"