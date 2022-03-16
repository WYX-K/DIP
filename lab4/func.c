#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "typedef.h"

int cmp(const void *a, const void *b);

Image *HistogramEnhancementLocalImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Histogram Enhancement Local");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + zero1;
    int matrixHeight = image->Height + zero2;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++, tempout++) {
            float array[256];
            memset(array, 0, sizeof(array));
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++) {
                    array[matrix[i - zero1 / 2 + m][j - zero2 / 2 + n]]++;
                }
            }
            for (int i = 0; i < 256; i++) {
                array[i] /= number1 * number2;
            }
            int res[256];
            memset(res, 0, sizeof(res));
            for (int i = 0; i < 256; i++) {
                float sum = 0.0;
                for (int j = 0; j <= i; j++) {
                    sum += array[j];
                }
                res[i] = round(sum * 255);
            }
            *tempout = res[matrix[i][j]];
        }
    }

    return (outimage);
}

Image *HistogramEnhancementGlobalImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Histogram Enhancement Global");
    tempin = image->data;
    tempout = outimage->data;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    float array[256];
    memset(array, 0, sizeof(array));

    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++) {
            array[matrix[i][j]]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        array[i] /= matrixWidth * matrixHeight;
    }

    int res[256];
    memset(res, 0, sizeof(res));

    for (int i = 0; i < 256; i++) {
        float sum = 0.0;
        for (int j = 0; j <= i; j++) {
            sum += array[j];
        }
        res[i] = round(sum * 255);
    }

    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempout++) {
            *tempout = res[matrix[i][j]];
        }
    }

    return (outimage);
}

Image *GammaCorrectionImage(Image *image, float gamma) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Gamma Correction");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width;
    int matrixHeight = image->Height;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempout++) {
            int res = (matrixWidth - 1) * pow((float)matrix[i][j] / matrixWidth, gamma);
            *tempout = res;
        }
    }

    // compute the variances of the resulted images

    float sum = 0.0;
    tempout = outimage->data;
    for (int i = 0; i < matrixWidth * matrixHeight; i++, tempout++) {
        sum += *tempout;
    }
    float mean = sum / (matrixWidth * matrixHeight);
    sum = 0.0;
    tempout = outimage->data;
    for (int i = 0; i < matrixWidth * matrixHeight; i++, tempout++) {
        sum += pow(*tempout - mean, 2);
    }
    float var = sum / (matrixWidth * matrixHeight);

    printf("The variance of Gamma Correction(%0.2f) is %0.2f.\n", gamma, var);
    return (outimage);
}

Image *SobelImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Sobel Sharpen Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + 2;
    int matrixHeight = image->Height + 2;
    int filter_x[3][3] = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}};
    int filter_y[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 1; i < matrixWidth - 1; i++) {
        for (int j = 1; j < matrixHeight - 1; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 1; i < matrixWidth - 1; i++) {
        for (int j = 1; j < matrixHeight - 1; j++, tempout++) {
            int res_x = 0;
            int res_y = 0;
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    res_x += matrix[i - 1 + m][j - 1 + n] * filter_x[m][n];
                    res_y += matrix[i - 1 + m][j - 1 + n] * filter_y[m][n];
                }
            }
            int res = sqrt(pow(res_x, 2) + pow(res_y, 2));
            if (res < 0) {
                res = 0;
            } else if (res > 255) {
                res = 255;
            }
            *tempout = res;
        }
    }

    return (outimage);
}

Image *LaplacianImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Laplacian Sharpen Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + 2;
    int matrixHeight = image->Height + 2;
    int filter[3][3] = {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}};

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 1; i < matrixWidth - 1; i++) {
        for (int j = 1; j < matrixHeight - 1; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 1; i < matrixWidth - 1; i++) {
        for (int j = 1; j < matrixHeight - 1; j++, tempout++) {
            int res = 0;
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    res += matrix[i - 1 + m][j - 1 + n] * filter[m][n];
                }
            }
            res = matrix[i][j] + (float)res * 0.5;
            if (res < 0) {
                res = 0;
            } else if (res > 255) {
                res = 255;
            }
            *tempout = res;
        }
    }

    return (outimage);
}

Image *ShearImage(Image *image, int type, float number) {
    if (number > 1) {
        printf("The number must be smaller than 1!");
        exit(0);
    }
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = image->Height;
    int newImg_Width = image->Width;
    if (type == 0) {
        newImg_Width += number * 300;
    } else {
        newImg_Height += number * 300;
    }
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, "#Shear");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newImg_Height; i++) {
        for (int j = 0; j < newImg_Width; j++, tempout++) {
            int v = i;
            int w = j;
            if (type == 0) {
                w = j - number * i;
            } else {
                v = i - number * j;
            }
            if (w >= 0 && w < matrixWidth && v < matrixHeight && v >= 0) {
                *tempout = matrix[v][w];
            } else {
                *tempout = 255;
            }
        }
    }

    return (outimage);
}

Image *RotationImage(Image *image, float theta) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = sqrt(pow(image->Height, 2) + pow(image->Width, 2));
    int newImg_Width = newImg_Height;
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, "#Rotation");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    int temp_x = (newImg_Height - matrixHeight) / 2;
    int temp_y = (newImg_Width - matrixWidth) / 2;
    int x0 = newImg_Height / 2;
    int y0 = x0;
    double val = PI / 180.0;
    for (int i = 0; i < newImg_Height; i++) {
        for (int j = 0; j < newImg_Width; j++, tempout++) {
            int v = (i - x0) * cos(theta * val) + (j - y0) * sin(theta * val) + x0 - temp_x;
            int w = (j - y0) * cos(theta * val) - (i - x0) * sin(theta * val) + x0 - temp_y;
            if (w >= 0 && w < matrixWidth && v < matrixHeight && v >= 0) {
                *tempout = matrix[v][w];
            } else {
                *tempout = 255;
            }
        }
    }

    return (outimage);
}

Image *TranslationImage(Image *image, int x_number, int y_number) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = image->Height + abs(y_number);
    int newImg_Width = image->Width + abs(x_number);
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, "#Translation");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newImg_Height; i++) {
        for (int j = 0; j < newImg_Width; j++, tempout++) {
            int x = i, y = j;
            if (y_number >= 0) {
                x = i - y_number;
            }
            if (x_number >= 0) {
                y = j - x_number;
            }
            if (x >= 0 && y >= 0 && x < matrixHeight && y < matrixWidth) {
                *tempout = matrix[x][y];
            } else {
                *tempout = 255;
            }
        }
    }

    return (outimage);
}

Image *NegativeImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Width, image->Height, "#Negative");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempout++) {
            *tempout = 255 - matrix[i][j];
        }
    }

    return (outimage);
}

Image *BilinearInterpolationImage(Image *image, float number) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = image->Height * number;
    int newImg_width = image->Width * number;
    outimage = CreateNewImage(image, newImg_Height, newImg_width, "#Bilinear Interpolation");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newImg_width; i++) {
        for (int j = 0; j < newImg_Height; j++, tempout++) {
            float p = i / number;
            float q = j / number;
            int new_pre_x = (int)p;
            int new_pre_y = (int)q;
            p = 1 / p;
            q = 1 / q;
            if (new_pre_x > matrixWidth - 2) {
                new_pre_x = matrixWidth - 2;
            }
            if (new_pre_y > matrixWidth - 2) {
                new_pre_y = matrixWidth - 2;
            }
            int piont1 = matrix[new_pre_x][new_pre_y];
            int piont2 = matrix[new_pre_x][new_pre_y + 1];
            int piont3 = matrix[new_pre_x + 1][new_pre_y];
            int piont4 = matrix[new_pre_x + 1][new_pre_y + 1];

            *tempout = (1 - p) * (1 - q) * piont1 + (1 - p) * q * piont2 + p * (1 - q) * piont3 + p * q * piont4;
        }
    }

    return (outimage);
}

Image *NearestNeighborImage(Image *image, float number) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = image->Height * number;
    int newImg_width = image->Width * number;
    outimage = CreateNewImage(image, newImg_Height, newImg_width, "#Nearest Neighbor Interpolation");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newImg_width; i++) {
        for (int j = 0; j < newImg_Height; j++, tempout++) {
            // round
            int pre_x = round(i / number);
            int pre_y = round(j / number);
            if (pre_x > matrixWidth - 1) {
                pre_x = matrixWidth - 1;
            }
            if (pre_y > matrixWidth - 1) {
                pre_y = matrixWidth - 1;
            }
            *tempout = matrix[pre_x][pre_y];
        }
    }

    return (outimage);
}

Image *PixelReplicationImage(Image *image, float number) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int newImg_Height = image->Height * number;
    int newImg_width = image->Width * number;
    outimage = CreateNewImage(image, newImg_Height, newImg_width, "#Pixel Replication");
    tempin = image->data;
    tempout = outimage->data;
    // Store existing images into arrays
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newImg_width; i++) {
        for (int j = 0; j < newImg_Height; j++, tempout++) {
            // round down
            int pre_x = i / number;
            int pre_y = j / number;
            if (pre_x > matrixWidth - 1) {
                pre_x = matrixWidth - 1;
            }
            if (pre_y > matrixWidth - 1) {
                pre_y = matrixWidth - 1;
            }
            *tempout = matrix[pre_x][pre_y];
        }
    }

    return (outimage);
}

Image *ReadPNMImage(char *filename) {
    char ch;
    int maxval, Width, Height;
    int size, num, j;
    FILE *fp;
    Image *image;
    int num_comment_lines = 0;

    image = (Image *)malloc(sizeof(Image));

    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Cannot open %s\n", filename);
        exit(0);
    }

    printf("Loading %s ...", filename);

    if (fscanf(fp, "P%c\n", &ch) != 1) {
        printf("File is not in ppm/pgm raw format; cannot read\n");
        exit(0);
    }
    if (ch != '6' && ch != '5') {
        printf("File is not in ppm/pgm raw format; cannot read\n");
        exit(0);
    }

    if (ch == '5')
        image->Type = GRAY; // Gray (pgm)
    else if (ch == '6')
        image->Type = COLOR; // Color (ppm)
    /* skip comments */
    ch = getc(fp);
    j = 0;
    while (ch == '#') {
        image->comments[num_comment_lines][j] = ch;
        j++;
        do {
            ch = getc(fp);
            image->comments[num_comment_lines][j] = ch;
            j++;
        } while (ch != '\n'); /* read to the end of the line */
        image->comments[num_comment_lines][j - 1] = '\0';
        j = 0;
        num_comment_lines++;
        ch = getc(fp); /* thanks, Elliot */
    }

    if (!isdigit((int)ch)) {
        printf("Cannot read header information from ppm file");
        exit(0);
    }

    ungetc(ch, fp); /* put that digit back */

    /* read the width, height, and maximum value for a pixel */
    fscanf(fp, "%d%d%d\n", &Width, &Height, &maxval);

    if (image->Type == GRAY)
        size = Width * Height;
    else if (image->Type == COLOR)
        size = Width * Height * 3;
    image->data = (unsigned char *)malloc(size);
    image->Width = Width;
    image->Height = Height;
    image->num_comment_lines = num_comment_lines;

    if (!image->data) {
        printf("cannot allocate memory for new image");
        exit(0);
    }

    num = fread((void *)image->data, 1, (size_t)size, fp);
    // printf("Complete reading of %d bytes \n", num);
    if (num != size) {
        printf("cannot read image data from file");
        exit(0);
    }

    // for (j = 0; j < image->num_comment_lines; j++) {
    //     printf("%s\n", image->comments[j]);
    // }

    fclose(fp);

    /*-----  Debug  ------*/

    if (image->Type == GRAY)
        printf("..Image Type PGM\n");
    else
        printf("..Image Type PPM Color\n");

    return (image);
}

Image *CreateNewImage(Image *image, int height, int width, char *comment) {
    Image *outimage;
    int size, j;

    outimage = (Image *)malloc(sizeof(Image));

    outimage->Type = image->Type;
    if (outimage->Type == GRAY)
        size = height * width;
    else if (outimage->Type == COLOR)
        size = height * width * 3;

    outimage->Width = width;
    outimage->Height = height;
    outimage->num_comment_lines = image->num_comment_lines;

    /*--------------------------------------------------------*/
    /* Copy Comments for Original Image      */
    for (j = 0; j < outimage->num_comment_lines; j++)
        strcpy(outimage->comments[j], image->comments[j]);

    /*----------- Add New Comment  ---------------------------*/
    strcpy(outimage->comments[outimage->num_comment_lines], comment);
    outimage->num_comment_lines++;

    outimage->data = (unsigned char *)malloc(size);
    if (!outimage->data) {
        printf("cannot allocate memory for new image");
        exit(0);
    }
    return (outimage);
}

void SavePNMImage(Image *temp_image, char *filename) {
    int num, j;
    int size;
    FILE *fp;

    printf("Saving Image %s\n", filename);
    fp = fopen(filename, "wb");
    if (!fp) {
        printf("cannot open file for writing");
        exit(0);
    }

    if (temp_image->Type == GRAY) { // Gray (pgm)
        fprintf(fp, "P5\n");
        size = temp_image->Width * temp_image->Height;
    } else if (temp_image->Type == COLOR) { // Color (ppm)
        fprintf(fp, "P6\n");
        size = temp_image->Width * temp_image->Height * 3;
    }

    for (j = 0; j < temp_image->num_comment_lines; j++)
        fprintf(fp, "%s\n", temp_image->comments[j]);

    fprintf(fp, "%d %d\n%d\n", temp_image->Width, temp_image->Height, 255);

    num = fwrite((void *)temp_image->data, 1, (size_t)size, fp);

    if (num != size) {
        printf("cannot write image data to file");
        exit(0);
    }

    fclose(fp);
}

Image *AverFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Average Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + zero1;
    int matrixHeight = image->Height + zero2;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++) {
            matrix[i][j] = *tempin;
            tempin++;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++) {
            int res = 0;
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++) {
                    res += matrix[i - zero1 / 2 + m][j - zero2 / 2 + n];
                }
            }
            *tempout = res / (number1 * number2);
            tempout++;
        }
    }

    return (outimage);
}

Image *MidFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, "#Mid Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + zero1;
    int matrixHeight = image->Height + zero2;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++) {
            matrix[i][j] = *tempin;
            tempin++;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++) {
            int arry[number1 * number2], k = 0;
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++, k++) {
                    arry[k] = matrix[i - zero1 / 2 + m][j - zero2 / 2 + n];
                }
            }
            qsort(arry, number1 * number2, sizeof(int), cmp);
            *tempout = arry[number1 * number2 / 2];
            tempout++;
        }
    }

    return (outimage);
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}