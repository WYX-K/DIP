#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "typedef.h"
#include "funcdef.h"

int cmp(const void *a, const void *b);

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

Image *CreateNewImage(Image *image, char *comment) {
    Image *outimage;
    int size, j;

    outimage = (Image *)malloc(sizeof(Image));

    outimage->Type = image->Type;
    if (outimage->Type == GRAY)
        size = image->Width * image->Height;
    else if (outimage->Type == COLOR)
        size = image->Width * image->Height * 3;

    outimage->Width = image->Width;
    outimage->Height = image->Height;
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

int AverFilter(char *filename, char *outfilename, int number1, int number2) {
    Image *image;
    Image *outimage;

    image = ReadPNMImage(filename);
    outimage = AverFilterImage(image, number1, number2);
    SavePNMImage(outimage, outfilename);

    return (0);
}

Image *AverFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int size;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, "#Average Filter");
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

int MidFilter(char *filename, char *outfilename, int number1, int number2) {
    Image *image;
    Image *outimage;

    image = ReadPNMImage(filename);
    outimage = MidFilterImage(image, number1, number2);
    SavePNMImage(outimage, outfilename);

    return (0);
}

Image *MidFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int size;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, "#Mid Filter");
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