#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "typedef.h"

int cmp(const void *a, const void *b);

Image *NegativeImage(Image *image) {
    unsigned char *tempin, *tempout;
    int size;
    Image *outimage;
    outimage = CreateNewImage(image, image->Width, image->Height, "#Bilinear Interpolation");
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
        for (int j = 0; j < matrixWidth; j++, tempout++) {
            *tempout = 255 - matrix[i][j];
        }
    }

    return (outimage);
}

Image *BilinearInterpolationImage(Image *image, float number) {
    unsigned char *tempin, *tempout;
    int size;
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
    int size;
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

Image *PixelReplication(Image *image, float number) {
    unsigned char *tempin, *tempout;
    int size;
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
    int size;
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
        for (int j = zero2 / 2; j < matrixHeight - zero1 / 2; j++) {
            matrix[i][j] = *tempin;
            tempin++;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero1 / 2; j++) {
            int res = 0;
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++) {
                    res += matrix[i - zero1 / 2 + m][j - zero2 / 2 + n];
                }
            }
            matrix[i][j] = res / (number1 * number2);
            *tempout = matrix[i][j];
            tempout++;
        }
    }

    return (outimage);
}

Image *MidFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int size;
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
        for (int j = zero2 / 2; j < matrixHeight - zero1 / 2; j++) {
            matrix[i][j] = *tempin;
            tempin++;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero1 / 2; j++) {
            int arry[number1 * number2], k = 0;
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++, k++) {
                    arry[k] = matrix[i - zero1 / 2 + m][j - zero2 / 2 + n];
                }
            }
            qsort(arry, number1 * number2, sizeof(int), cmp);
            matrix[i][j] = arry[number1 * number2 / 2];
            *tempout = matrix[i][j];
            tempout++;
        }
    }

    return (outimage);
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}