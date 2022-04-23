Image *NotOverlapPartImage(Image *image) {
    int height = image->Height;
    int width = image->Width;
    int size = height * width;
    Image *tempimage1;
    Image *tempimage2;
    Image *outimage = CreateNewImage(image, height, width, (char *)"#NotOverlapPart Image");
    tempimage1 = OverlapPartImage(image);
    printf("OverlapPartImage\n");
    tempimage2 = ConnBorderImage(image);
    printf("ConnBorderImage\n");
    unsigned char *tempin = image->data;
    unsigned char *temp1 = tempimage1->data;
    unsigned char *temp2 = tempimage2->data;
    unsigned char *tempout = outimage->data;
    for (int i = 0; i < size; i++) {
        tempout[i] = tempin[i] - temp1[i] - temp2[i];
    }

    return outimage;
}

Image *OverlapPartImage(Image *image) {
    int height = image->Height;
    int width = image->Width;
    int size = height * width;
    Pixel *pixel = (Pixel *)malloc(sizeof(Pixel) * size);
    Image *outimage = CreateNewImage(image, height, width, (char *)"#OverlapPart Image");
    outimage = ConnBorderImage(image);
    unsigned char *tempin = image->data;
    unsigned char *tempout = outimage->data;
    for (int i = 0; i < size; i++) {
        tempout[i] = tempin[i] - tempout[i];
    }

    unsigned char *A = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memcpy(A, tempout, size);
    unsigned char *X1 = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(X1, 0, sizeof(unsigned char) * size);
    unsigned char *X2 = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(X2, 0, sizeof(unsigned char) * size);
    unsigned char *B = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(B, 0, sizeof(unsigned char) * size);
    int *num = (int *)malloc(sizeof(int) * size);
    memset(num, 0, sizeof(int) * size);
    int n = 400;
    int count = 0;
    while (find(A, 255, pixel, height, width)) {
        X1[pixel[0].y * width + pixel[0].x] = 255;
        while (1) {
            unsigned char *Xp1 = (unsigned char *)malloc(sizeof(unsigned char) * size);
            memcpy(Xp1, X1, size);
            X1 = Dilation(X1, height, width, 0);
            for (int i = 0; i < size; i++) {
                if (X1[i] > A[i]) {
                    X1[i] = A[i];
                }
            }
            if (memcmp(Xp1, X1, size) == 0) {
                break;
            }
            free(Xp1);
        }
        num[count] = find(X1, 255, pixel, height, width);
        if (num[count] > n) {
            for (int i = 0; i < size; i++) {
                if (X2[i] < X1[i]) {
                    X2[i] = X1[i];
                }
            }
        }
        count++;
        for (int i = 0; i < size; i++) {
            if (B[i] < X1[i]) {
                B[i] = X1[i];
            }
        }
        memset(X1, 0, sizeof(unsigned char) * size);
        for (int i = 0; i < size; i++) {
            A[i] -= B[i];
            if (A[i] < 100) {
                A[i] = 0;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        tempout[i] = X2[i];
    }

    free(pixel);
    free(A);
    free(X1);
    free(B);
    free(X2);
    free(num);
    return outimage;
}

Image *ConnBorderImage(Image *image) {
    int height = image->Height;
    int width = image->Width;
    int size = height * width;
    Image *outimage = CreateNewImage(image, height, width, (char *)"#ConnBorder Image");
    unsigned char *tempin = image->data;
    unsigned char *tempout = outimage->data;
    unsigned char *B = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(B, 0, sizeof(unsigned char) * size);

    B[0] = 255;
    while (1) {
        unsigned char *Xp1 = (unsigned char *)malloc(sizeof(unsigned char) * size);
        memcpy(Xp1, B, size);
        B = Dilation(B, height, width, 1);
        for (int i = 0; i < size; i++) {
            if (B[i] > tempin[i]) {
                B[i] = tempin[i];
            }
        }
        if (memcmp(Xp1, B, size) == 0) {
            break;
        }
        free(Xp1);
    }
    for (int i = 0; i < size; i++) {
        tempout[i] = B[i];
    }
    free(B);

    return outimage;
}

void CountConnPixel(Image *image, char *output) {
    int height = image->Height;
    int width = image->Width;
    int size = height * width;
    Pixel *pixel = (Pixel *)malloc(sizeof(Pixel) * size);
    unsigned char *A = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memcpy(A, image->data, size);
    unsigned char *X1 = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(X1, 0, sizeof(unsigned char) * size);
    unsigned char *B = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(B, 0, sizeof(unsigned char) * size);
    int *num = (int *)malloc(sizeof(int) * size);
    memset(num, 0, sizeof(int) * size);

    int count = 0;
    FILE *fp = fopen(output, "w");

    while (find(A, 255, pixel, height, width)) {
        X1[pixel[0].y * width + pixel[0].x] = 255;
        while (1) {
            unsigned char *Xp1 = (unsigned char *)malloc(sizeof(unsigned char) * size);
            memcpy(Xp1, X1, size);
            X1 = Dilation(X1, height, width, 0);
            for (int i = 0; i < size; i++) {
                if (X1[i] > A[i]) {
                    X1[i] = A[i];
                }
            }
            if (memcmp(Xp1, X1, size) == 0) {
                break;
            }
            free(Xp1);
        }
        num[count] = find(X1, 255, pixel, height, width);
        fprintf(fp, "The number of %d th is %d\n", count, num[count]);
        for (int i = 0; i < size; i++) {
            if (B[i] < X1[i]) {
                B[i] = X1[i];
            }
        }
        memset(X1, 0, sizeof(unsigned char) * size);
        for (int i = 0; i < size; i++) {
            A[i] -= B[i];
            if (A[i] < 100) {
                A[i] = 0;
            }
        }
        count++;
    }
    free(pixel);
    free(A);
    free(X1);
    free(B);
    free(num);
    fclose(fp);
    printf("Finshed!\n");
}

Image *ExtractBoundariesImage(Image *image) {
    Image *outimage;
    outimage = ErosionImage(image);
    int size = image->Height * image->Width;

    for (int i = 0; i < size; i++) {
        outimage->data[i] = image->data[i] - outimage->data[i];
    }

    return outimage;
}

Image *CloseImage(Image *image) {
    Image *outimage;
    outimage = DilationImage(image);
    outimage = ErosionImage(outimage);
    return outimage;
}

Image *OpenImage(Image *image) {
    Image *outimage;
    outimage = ErosionImage(image);
    outimage = DilationImage(outimage);
    return outimage;
}

Image *ErosionImage(Image *image) {
    int height = image->Height;
    int width = image->Width;
    Image *outimage = CreateNewImage(image, height, width, (char *)"#Erosion Image");
    unsigned char *tempin = image->data;
    unsigned char *tempout = outimage->data;
    int *matrix = (int *)malloc(sizeof(int) * height * width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i * width + j] = tempin[i * width + j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                matrix[i * width + j] = tempin[i * width + j];
            } else {
                int min = 255;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (tempin[(i + k) * width + j + l] < min) {
                            min = tempin[(i + k) * width + j + l];
                        }
                    }
                }
                matrix[i * width + j] = min;
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tempout[i * width + j] = matrix[i * width + j];
        }
    }
    free(matrix);
    return outimage;
}

Image *DilationImage(Image *image) {
    int height = image->Height;
    int width = image->Width;
    Image *outimage = CreateNewImage(image, height, width, (char *)"#Dilation Image");
    unsigned char *tempin = image->data;

    outimage->data = Dilation(tempin, height, width, 0);
    return outimage;
}

Image *RectNotchBandrejectImage(Image *image, int Rectheight, int Rectwidth) {
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width;
    int height = image->Height;
    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < Rectheight && j < (width + Rectwidth) / 2 && j > (width - Rectwidth) / 2 || i > height - Rectheight && j < (width + Rectwidth) / 2 && j > (width - Rectwidth) / 2) {
                src[i * width + j].x = 0;
                src[i * width + j].y = 0;
            }
        }
    }

    fft(src, src, -1, height, width);
    outimage = CreateNewImage(image, height, width, (char *)"#RectNotchBandreject img");
    // outimage->data = Normal(getResult(src, size), size, 255);

    for (int i = 0; i < size; i++) {
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *ZeroPadding(Image *image, int height, int width) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int newWidth = matrixWidth + width;
    int newHeight = matrixHeight + height;

    outimage = CreateNewImage(image, newHeight, newWidth, (char *)"#ZeroPadding img");

    tempin = image->data;
    tempout = outimage->data;

    int **matrix = new int *[matrixWidth];
    for (int i = 0; i < matrixWidth; i++) {
        matrix[i] = new int[matrixHeight];
    }

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++, tempout++) {
            if (i < matrixHeight && j < matrixWidth) {
                *tempout = matrix[i][j];
            } else {
                *tempout = 0;
            }
        }
    }

    return (outimage);
}

Image *RemoveZeros(Image *image, int height, int width) {
    int matrixWidth = image->Width, matrixHeight = image->Height;
    Image *outimage = CreateNewImage(image, image->Height - height, image->Width - width, (char *)"#RemoveZeros Image");
    unsigned char *tempout;
    tempout = outimage->data;
    unsigned char *tempin;
    tempin = image->data;
    int **matrix = new int *[matrixWidth];
    for (int i = 0; i < matrixWidth; i++) {
        matrix[i] = new int[matrixHeight];
    }
    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < matrixHeight - height; i++) {
        for (int j = 0; j < matrixWidth - width; j++, tempout++) {
            *tempout = matrix[i][j];
        }
    }

    return outimage;
}

Image *AdMedFilterImage(Image *image, int n, int smax) {
    unsigned char *tempin, *tempout;

    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#AdMedFilter Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width;
    int matrixHeight = image->Height;

    memcpy(tempout, tempin, matrixWidth * matrixHeight);

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    int pos = (smax - 1) / 2;
    for (int i = pos; i < matrixWidth - pos; i++) {
        for (int j = pos; j < matrixHeight - pos; j++) {
            int size = n;
            while (size <= smax) {
                int lens = size * size;
                int arry[lens];
                int k = 0;
                for (int x = 0; x < size; x++) {
                    for (int y = 0; y < size; y++, k++) {
                        arry[k] = matrix[i - (size - 1) / 2 + x][j - (size - 1) / 2 + y];
                    }
                }
                qsort(arry, lens, sizeof(int), cmp);
                int zmin = arry[0];
                int zmed = arry[(lens - 1) / 2];
                int zmax = arry[lens - 1];
                int z = matrix[i][j];
                int a1 = zmed - zmin;
                int a2 = zmed - zmax;
                if (a1 > 0 && a2 < 0) {
                    int b1 = z - zmin, b2 = z - zmax;
                    if (b1 > 0 && b2 < 0) {
                        tempout[i * matrixWidth + j] = z;
                    } else {
                        tempout[i * matrixWidth + j] = zmed;
                    }
                    break;
                } else {
                    size += 2;
                    if (size > smax) {
                        tempout[i * matrixWidth + j] = z;
                        break;
                    }
                }
            }
        }
    }

    for (int k = 0; k < pos; k++)
        for (int l = pos; l < matrixWidth - pos; l++)
            tempout[k * matrixWidth + l] = tempout[pos * matrixWidth + l];
    for (int a = matrixHeight - pos; a < matrixHeight; a++)
        for (int b = pos; b < matrixWidth - pos; b++)
            tempout[a * matrixWidth + b] = tempout[(matrixHeight - pos - 1) * matrixWidth + b];
    for (int c = 0; c < pos; c++)
        for (int d = 0; d < matrixHeight; d++)
            tempout[d * matrixWidth + c] = tempout[d * matrixWidth + pos];
    for (int e = matrixWidth - pos; e < matrixWidth; e++)
        for (int f = 0; f < matrixHeight; f++)
            tempout[f * matrixWidth + e] = tempout[f * matrixWidth + matrixWidth - pos - 1];

    return (outimage);
}

Image *AlphaTrimmedMeanImage(Image *image, int number1, int number2, int d) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Alpha Trimmed Mean Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + zero1;
    int matrixHeight = image->Height + zero2;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 1, sizeof(matrix));
    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++, tempin++) {
            matrix[i][j] = *tempin;
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
            int res = 0;
            for (int k = d / 2; k < number1 * number2 - d / 2; k++) {
                res += arry[k];
            }
            res /= number1 * number2 - d;
            *tempout = res;
            tempout++;
        }
    }

    return (outimage);
}

Image *GeoFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#GeoFilter Filter");
    tempin = image->data;
    tempout = outimage->data;

    int matrixWidth = image->Width + zero1;
    int matrixHeight = image->Height + zero2;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 1, sizeof(matrix));
    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = zero1 / 2; i < matrixWidth - zero1 / 2; i++) {
        for (int j = zero2 / 2; j < matrixHeight - zero2 / 2; j++, tempout++) {
            double res = 1;
            for (int m = 0; m < number1; m++) {
                for (int n = 0; n < number2; n++) {
                    res *= pow(matrix[i - zero1 / 2 + m][j - zero2 / 2 + n], 1.0 / (number1 * number2));
                }
            }
            if (res > 255)
                res = 255;
            if (res < 0)
                res = 0;
            *tempout = res;
            // printf("%d\n", *tempout);
        }
    }

    return (outimage);
}

Image *AddSinNoiseImage(Image *image, float sigma) {
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Add Sin Noise");

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    int *src = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; ++i) {
        src[i] = 1.0 * image->data[i];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            src[i * width + j] += sigma * sin(i + j);
        }
    }

    for (int i = 0; i < size; i++) {
        if (src[i] > 255) {
            src[i] = 255;
        }
        if (src[i] < 0) {
            src[i] = 0;
        }
        outimage->data[i] = src[i];
    }

    return (outimage);
}

Image *IDealNotchBandrejectImage(Image *image, float d0, int x, int y) {
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width;
    int height = image->Height;
    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des1 = sqrt(pow(i - x, 2) + pow(j - y, 2));
            double des2 = sqrt(pow(i - (height - x), 2) + pow(j - (width - y), 2));
            // double p = -0.5 * pow((double)(pow(des, 2) - pow(c, 2)) / (des * w), 2);
            // src[i * width + j].x *= (double)(1 - exp(p));
            if (des1 < d0 || des2 < d0) {
                src[i * width + j].x = 0;
            }
        }
    }

    // fft(src, src, -1, height, width);
    outimage = CreateNewImage(image, height, width, (char *)"#IDealNotchBandreject img");
    outimage->data = Normal(getResult(src, size), size, 255);

    for (int i = 0; i < size; i++) {
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *HomomorphicImage(Image *image, float radius, float gamma1, float gamma2, float c) {
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        if (image->data[i] == 0) {
            src[i].x = 0.0;
        } else {
            src[i].x = 1.0 * log(image->data[i]);
        }
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            double p = -c * pow(des / radius, 2);
            src[i * width + j].x *= (gamma1 - gamma2) * (1 - exp(p)) + gamma2;
        }
    }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#Homomorphic img");

    for (int i = 0; i < size; i++) {
        outimage->data[i] = exp(src[i].x);
    }

    return (outimage);
}

Image *BHPF_TImage(Image *image, float radius, float rank) {
    unsigned char *tempout;
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            src[i * width + j].x *= 1 - 1 / (1 + pow(des / radius, 2 * rank));
        }
    }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#BHPF_T img");

    for (int i = 0; i < size; i++) {
        if (src[i].x < 100) {
            src[i].x = 0;
        } else {
            src[i].x = 255;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *GLPFImage(Image *image, float radius) {
    unsigned char *tempout;
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            double p = -1 / 2 * pow(des / radius, 2);
            src[i * width + j].x *= exp(p);
        }
    }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#GLPF img");

    for (int i = 0; i < size; i++) {
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *BLPFImage(Image *image, float radius, float rank) {
    unsigned char *tempout;
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            src[i * width + j].x *= 1 / (1 + pow(des / radius, 2 * rank));
        }
    }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#BLPF img");

    for (int i = 0; i < size; i++) {
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *ILPFImage(Image *image, float radius) {
    unsigned char *tempout;
    Image *outimage;

    int size = image->Height * image->Width;
    int width = image->Width, height = image->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            if (des > radius) {
                src[i * width + j].x = 0;
            }
        }
    }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#ILPF img");

    for (int i = 0; i < size; i++) {
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = src[i].x;
    }

    return (outimage);
}

Image *FFTImage(Image *image) {
    int size = image->Height * image->Width;
    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * image->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, image->Height, image->Width);

    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"FFT result");
    outimage->data = Normal(getResult(src, size), size, 255);

    return (outimage);
}

Image *MagnitudeImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Magnitude Reconstruction");
    tempin = image->data;
    tempout = outimage->data;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int size = matrixHeight * matrixWidth;
    int matrix[matrixWidth][matrixHeight];
    int c = matrixHeight;
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    printf("Begin!...\n");

    double re, im, temp;
    double Magnitude[matrixWidth][matrixHeight];

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++) {
            re = 0;
            im = 0;
            for (int x = 0; x < matrixHeight; x++) {
                for (int y = 0; y < matrixWidth; y++) {
                    temp = (double)i * x / (double)matrixHeight + (double)j * y / (double)matrixWidth;
                    re += matrix[x][y] * cos(-2 * PI * temp);
                    im += matrix[x][y] * sin(-2 * PI * temp);
                }
            }
            Magnitude[i][j] = sqrt(pow(re, 2) + pow(im, 2));
        }
    }

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempout++) {
            re = 0;
            for (int x = 0; x < matrixHeight; x++) {
                for (int y = 0; y < matrixWidth; y++) {
                    temp = (double)i * x / (double)matrixHeight + (double)j * y / (double)matrixWidth;
                    re += Magnitude[x][y] * cos(2 * PI * temp);
                }
            }
            int res = re / size;
            if (res < 0) {
                res = 0;
            } else if (res > 255) {
                res = 255;
            }
            *tempout = res;
        }
    }

    printf("Success!\n");

    return (outimage);
}

Image *PhaseAngleImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Phase Angle Reconstruction");
    tempin = image->data;
    tempout = outimage->data;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int size = matrixHeight * matrixWidth;

    int matrix[matrixWidth][matrixHeight];
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    double PhaseAngle[matrixWidth][matrixHeight];

    printf("Begin!...\n");

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++) {
            double re = 0;
            double im = 0;
            for (int x = 0; x < matrixHeight; x++) {
                for (int y = 0; y < matrixWidth; y++) {
                    double temp = (double)i * x / (double)matrixHeight + (double)j * y / (double)matrixWidth;
                    re += matrix[x][y] * cos(-2 * PI * temp);
                    im += matrix[x][y] * sin(-2 * PI * temp);
                }
            }
            PhaseAngle[i][j] = atan2(im, re);
        }
    }

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempout++) {
            double re = 0;
            for (int x = 0; x < matrixHeight; x++) {
                for (int y = 0; y < matrixWidth; y++) {
                    double temp = (double)i * x / (double)matrixHeight + (double)j * y / (double)matrixWidth;
                    re += cos(PhaseAngle[x][y] + 2 * PI * temp);
                }
            }
            int res = re;
            if (res < 0) {
                res = 0;
            } else if (res > 255) {
                res = 255;
            }
            *tempout = res;
        }
    }

    printf("Success!\n");

    return (outimage);
}

Image *DFTImage(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#DFT Transform");
    tempin = image->data;
    tempout = outimage->data;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int size = matrixHeight * matrixWidth;
    int matrix[matrixWidth][matrixHeight];
    int c = matrixHeight;
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++, tempin++) {
            matrix[i][j] = *tempin * pow(-1, i + j);
        }
    }

    printf("Begin!...\n");

    double re, im, temp;

    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempout++) {
            re = 0;
            im = 0;
            for (int x = 0; x < matrixHeight; x++) {
                for (int y = 0; y < matrixWidth; y++) {
                    temp = (double)i * x / (double)matrixHeight + (double)j * y / (double)matrixWidth;
                    re += matrix[x][y] * cos(-2 * PI * temp);
                    im += matrix[x][y] * sin(-2 * PI * temp);
                }
            }
            re = c * re / size;
            im = c * im / size;
            int res = 50 * log(1 + sqrt(pow(re, 2) + pow(im, 2)));
            if (res < 0) {
                res = 0;
            } else if (res > 255) {
                res = 255;
            }
            *tempout = res;
        }
    }

    printf("Success!\n");

    return (outimage);
}

Image *HistogramEnhancementLocalImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Histogram Enhancement Local");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Histogram Enhancement Global");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Gamma Correction");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Sobel Sharpen Filter");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Laplacian Sharpen Filter");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, (char *)"#Shear");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, (char *)"#Rotation");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_Width, (char *)"#Translation");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Negative");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_width, (char *)"#Bilinear Interpolation");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_width, (char *)"#Nearest Neighbor Interpolation");
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
    outimage = CreateNewImage(image, newImg_Height, newImg_width, (char *)"#Pixel Replication");
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

Image *AverFilterImage(Image *image, int number1, int number2) {
    unsigned char *tempin, *tempout;
    int zero1 = number1 - 1;
    int zero2 = number2 - 1;
    Image *outimage;
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Average Filter");
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
    outimage = CreateNewImage(image, image->Height, image->Width, (char *)"#Mid Filter");
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