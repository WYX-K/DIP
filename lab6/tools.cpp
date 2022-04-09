Image *BHPF_T(Image *image, float radius, float rank) {
    unsigned char *tempin, *tempout;
    Image *inimage, *outimage;

    inimage = ZeroPadding(image);
    tempin = inimage->data;
    int size = inimage->Height * inimage->Width;
    int width = inimage->Width, height = inimage->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * inimage->data[i];
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

Image *GLPF(Image *image, float radius) {
    unsigned char *tempin, *tempout;
    Image *inimage, *outimage;

    inimage = ZeroPadding(image);
    tempin = inimage->data;
    int size = inimage->Height * inimage->Width;
    int width = inimage->Width, height = inimage->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * inimage->data[i];
        src[i].y = 0.0;
    }

    fft(src, src, 1, height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
            double p = -(double)(1 / 2) * pow(des / radius, 2);
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

Image *BLPF(Image *image, float radius, float rank) {
    unsigned char *tempin, *tempout;
    Image *inimage, *outimage;

    inimage = ZeroPadding(image);
    tempin = inimage->data;
    int size = inimage->Height * inimage->Width;
    int width = inimage->Width, height = inimage->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * inimage->data[i];
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

Image *ILPF(Image *image, float radius) {
    unsigned char *tempin, *tempout;
    Image *inimage, *outimage;

    inimage = ZeroPadding(image);
    tempin = inimage->data;
    int size = inimage->Height * inimage->Width;
    int width = inimage->Width, height = inimage->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        src[i].x = 1.0 * inimage->data[i];
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

Image *ZeroPadding(Image *image) {
    unsigned char *tempin, *tempout;
    Image *outimage;
    int matrixWidth = image->Width;
    int matrixHeight = image->Height;
    int newWidth = image->Width * 2;
    int newHeight = image->Height * 2;

    outimage = CreateNewImage(image, newHeight, newWidth, (char *)"#temp img");
    tempin = image->data;
    tempout = outimage->data;

    int matrix[matrixHeight][matrixWidth];
    memset(matrix, 0, sizeof(matrix));
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

Image *RemoveZeros(Image *image) {
    int matrixWidth = image->Width, matrixHeight = image->Height;

    Image *outimage = CreateNewImage(image, image->Height / 2, image->Width / 2, (char *)"#BLPF Image");
    unsigned char *tempout;
    tempout = outimage->data;
    unsigned char *tempin;
    tempin = image->data;

    int matrix[matrixHeight][matrixWidth];

    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++, tempin++) {
            matrix[i][j] = *tempin;
        }
    }

    for (int i = 0; i < matrixHeight / 2; i++) {
        for (int j = 0; j < image->Width / 2; j++, tempout++) {
            *tempout = matrix[i][j];
        }
    }

    return outimage;
}

void fft(struct _complex *src, struct _complex *dst, int flag, int height, int width) {
    int y, x, i, u, k, n;
    int NUM_y = height, NUM_x = width;
    double wu;
    struct _complex w, a0, a1, t;
    clock_t start, end;
    start = clock();
    // 鍌呴噷鍙舵鍙樻崲鏃讹紝灏嗕腑蹇冨钩绉诲埌鍥涜竟
    if (flag == -1)
        fft_shift(src, NUM_y, NUM_x);
    // 瀵箈姣忎竴琛屽仛鍌呴噷鍙跺彉鎹�
    for (y = 0; y < NUM_y; y++) {
        // 鍏堝垎鍓叉暟缁�
        split_array(&src[y * NUM_x + 0], &dst[y * NUM_x + 0], NUM_x, 0, 0, NUM_y, NUM_x); // 瀵� x鍒嗙粍

        // 瀵� f[y][] 杩欎竴缁勬暟杩涜鍌呴噷鍙跺彉鎹�
        for (i = 0; i < log(1.0 * NUM_x) / log(2.0); i++) { //璁＄畻娆℃暟涓� 2^n = num锛屽嵆n = log2^num
            // 姣忔璁＄畻鐨勯棿闅旀槸 2^n,鍒嗗埆涓� 1锛�2锛�4锛�8
            n = 2 * pow(2.0, i);                // 鏈疆涓€缁勪釜鏁颁负 2 * 2^n锛屽垎鍒负 2,4,8,鍒欏ソ3杞�
            for (k = 0; k < NUM_x / n; k++) {   // num/n 涓哄綋鍓嶇殑缁勬暟锛屽垎鍒负 4锛�2锛�1
                for (u = 0; u < n / 2; u++) {   // 瀵规瘡缁勮繘琛岃绠�, a0 鍜� b0 鐨勪釜鏁板垎鍒负 n/2
                    wu = -1 * 2 * M_PI * u / n; // 璁＄畻鏃嬭浆鍥犲瓙
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  濡傛灉鏄倕閲屽彾閫嗗彉鎹紝姝ゅ flag = -1

                    a0 = dst[y * NUM_x + k * n + u];         // 濂囨暟椤� 	[y][k*n+u]
                    a1 = dst[y * NUM_x + k * n + u + n / 2]; // 鍋舵暟椤� 	[y][k*n+u+n/2]

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[y * NUM_x + k * n + u].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[y * NUM_x + k * n + u].y = a0.y + t.y;
                    dst[y * NUM_x + k * n + u + n / 2].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[y * NUM_x + k * n + u + n / 2].y = a0.y - t.y;
                }
            }
        }
        if (flag == 1) // 姝ｅ悜鏃讹紝闄や竴涓猉闀垮害锛岄伩鍏嶆暟鎹繃澶э紝鏈潵涓嶅簲璇ラ櫎鐨�
            for (u = 0; u < NUM_x; u++) {
                dst[y * NUM_x + u].x /= NUM_x;
                dst[y * NUM_x + u].y /= NUM_x;
            }
    }

    // 瀵箉姣忎竴鍒楀仛鍌呴噷鍙跺彉鎹�
    for (x = 0; x < NUM_x; x++) {
        // 鍏堝垎鍓叉暟缁�
        split_array(&dst[0 * NUM_x + x], &dst[0 * NUM_x + x], 0, NUM_y, 1, NUM_y, NUM_x); // 瀵� y鍒嗙粍

        // 瀵� f[][x] 杩欎竴缁勬暟杩涜鍌呴噷鍙跺彉鎹�
        for (i = 0; i < log(1.0 * NUM_y) / log(2.0); i++) { //璁＄畻娆℃暟涓� 2^n = num锛屽嵆n = log2^num
            // 姣忔璁＄畻鐨勯棿闅旀槸 2^n,鍒嗗埆涓� 1锛�2锛�4锛�8
            n = 2 * pow(2.0, i);                // 鏈疆涓€缁勪釜鏁颁负 2 * 2^n锛屽垎鍒负 2,4,8,鍒欏ソ3杞�
            for (k = 0; k < NUM_y / n; k++) {   // num/n 涓哄綋鍓嶇殑缁勬暟锛屽垎鍒负 4锛�2锛�1
                for (u = 0; u < n / 2; u++) {   // 瀵规瘡缁勮繘琛岃绠�, a0 鍜� b0 鐨勪釜鏁板垎鍒负 n/2
                    wu = -1 * 2 * M_PI * u / n; // 璁＄畻鏃嬭浆鍥犲瓙
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  濡傛灉鏄倕閲屽彾閫嗗彉鎹紝姝ゅ flag = -1

                    a0 = dst[(k * n + u) * NUM_x + x];         // 濂囨暟椤� 	[k*n+u][x]
                    a1 = dst[(k * n + u + n / 2) * NUM_x + x]; // 鍋舵暟椤� 		[(k*n + u + n/2)*NUM_y 	+ x ][x]

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[(k * n + u) * NUM_x + x].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[(k * n + u) * NUM_x + x].y = a0.y + t.y;
                    dst[(k * n + u + n / 2) * NUM_x + x].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[(k * n + u + n / 2) * NUM_x + x].y = a0.y - t.y;
                }
            }
        }
        if (flag == -1)
            for (u = 0; u < NUM_y; u++) {
                dst[u * NUM_x + x].x /= NUM_y;
                dst[u * NUM_x + x].y /= NUM_y;
            }
    }

    // 鍌呴噷鍙舵鍙樻崲鏃讹紝灏嗗洓杈瑰钩绉诲埌涓績
    if (flag == 1)
        fft_shift(dst, NUM_y, NUM_x);

    // 鎵撳嵃褰撳彉鎹㈢粨鏋�
    end = clock();
    printf("\n鍌呴噷鍙�%s鍙樻崲缁撴潫锛岃€楁椂%fs, NUM=%d x %d\n", flag == 1 ? "" : "閫�", (double)(end - start) / CLOCKS_PER_SEC, NUM_x, NUM_y);
}

double *getResult(struct _complex *src, int size) {
    int i;
    double *res = (double *)malloc(sizeof(double) * size);

    for (i = 0; i < size; ++i)
        res[i] = sqrt(src[i].x * src[i].x + src[i].y * src[i].y);

    return res;
}

void fft_shift(struct _complex *src, int height, int width) {
    int x, y, a, b;
    struct _complex tmp;
    int NUM_y = height, NUM_x = width;

    for (y = 0; y < NUM_y / 2; y++) {
        for (x = 0; x < NUM_x; x++) {
            a = y * NUM_x + x;
            b = ((y + NUM_y / 2) % NUM_y) * NUM_x + (NUM_x / 2 + x) % NUM_x;

            tmp = src[a];
            src[a] = src[b];
            src[b] = tmp;
        }
    }
}

void split_array(struct _complex *src, struct _complex *dst, int x_n, int y_n, int flag, int height, int width) {
    int i;
    int NUM_y = height, NUM_x = width;
    //	struct _complex t[flag == 0 ? x_n/2 : y_n/2];
    struct _complex *s = src, *d = dst;
    struct _complex *t = (struct _complex *)malloc(sizeof(struct _complex) * (flag == 0 ? x_n / 2 : y_n / 2));

    if (flag == 0) {
        if (x_n <= 1) return;

        for (i = 0; i < x_n / 2; i++) {
            t[i].x = s[i * 2 + 1].x; // 閺嗗倸鐡ㄦ總鍥ㄦ殶妞�?
            t[i].y = s[i * 2 + 1].y;

            d[i].x = s[i * 2].x; // 閹风柉绀夐崑鑸垫殶妞ょ懓鍩屾担搴濈秴
            d[i].y = s[i * 2].y;
        }
        for (i = 0; i < x_n / 2; i++) {
            d[i + x_n / 2].x = t[i].x; // 閹风柉绀夋總鍥ㄦ殶妞ょ懓鍩屾妯圭秴
            d[i + x_n / 2].y = t[i].y;
        }
        split_array(dst, dst, x_n / 2, y_n, flag, NUM_y, NUM_x);
        split_array(dst + x_n / 2, dst + x_n / 2, x_n / 2, y_n, flag, NUM_y, NUM_x);
    } else {
        if (y_n <= 1) return;

        for (i = 0; i < y_n / 2; i++) {
            t[i].x = s[(i * 2 + 1) * NUM_x].x; // 閺嗗倸鐡ㄦ總鍥ㄦ殶妞�?
            t[i].y = s[(i * 2 + 1) * NUM_x].y;

            d[i * NUM_x].x = s[(i * 2) * NUM_x].x; // 閹风柉绀夐崑鑸垫殶妞ょ懓鍩屾担搴濈秴
            d[i * NUM_x].y = s[(i * 2) * NUM_x].y;
        }
        for (i = 0; i < y_n / 2; i++) {
            d[(i + y_n / 2) * NUM_x].x = t[i].x; // 閹风柉绀夋總鍥ㄦ殶妞ょ懓鍩屾妯圭秴
            d[(i + y_n / 2) * NUM_x].y = t[i].y;
        }
        split_array(dst, dst, x_n, y_n / 2, flag, NUM_y, NUM_x);
        split_array(dst + NUM_x * y_n / 2, dst + NUM_x * y_n / 2, x_n, y_n / 2, flag, NUM_y, NUM_x);
    }
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
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