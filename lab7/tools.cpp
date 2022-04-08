Image *Bandreject(Image *image, float w, float c) {
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

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         double des = sqrt(pow(i - (double)height / 2, 2) + pow(j - (double)width / 2, 2));
    //         double p = -pow((pow(des, 2) - pow(c, 2)) / (des * w), 2);
    //         src[i * width + j].x *= (1 - exp(p));
    //     }
    // }

    fft(src, src, -1, height, width);

    outimage = CreateNewImage(image, height, width, (char *)"#Bandreject img");
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

Image *Homomorphic(Image *image, float radius, float gamma1, float gamma2, float c) {
    Image *inimage, *outimage;

    inimage = ZeroPadding(image);
    int size = inimage->Height * inimage->Width;
    int width = inimage->Width, height = inimage->Height;

    struct _complex *src = (struct _complex *)malloc(sizeof(struct _complex) * size);

    for (int i = 0; i < size; ++i) {
        if (inimage->data[i] == 0) {
            src[i].x = 0.0;
        } else {
            src[i].x = 1.0 * log(inimage->data[i]);
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
        if (src[i].x > 255) {
            src[i].x = 255;
        }
        if (src[i].x < 0) {
            src[i].x = 0;
        }
        outimage->data[i] = exp(src[i].x);
    }

    return (outimage);
}

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

Image *RemoveZeros(Image *image) {
    int matrixWidth = image->Width, matrixHeight = image->Height;
    Image *outimage = CreateNewImage(image, image->Height / 2, image->Width / 2, (char *)"#BLPF Image");
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
    // 傅里叶正变换时，将中心平移到四边
    if (flag == -1)
        fft_shift(src, NUM_y, NUM_x);
    // 对x每一行做傅里叶变换
    for (y = 0; y < NUM_y; y++) {
        // 先分割数组
        split_array(&src[y * NUM_x + 0], &dst[y * NUM_x + 0], NUM_x, 0, 0, NUM_y, NUM_x); // 对 x分组

        // 对 f[y][] 这一组数进行傅里叶变换
        for (i = 0; i < log(1.0 * NUM_x) / log(2.0); i++) { //计算次数为 2^n = num，即n = log2^num
            // 每次计算的间隔是 2^n,分别为 1，2，4，8
            n = 2 * pow(2.0, i);                // 本轮一组个数为 2 * 2^n，分别为 2,4,8,则好3轮
            for (k = 0; k < NUM_x / n; k++) {   // num/n 为当前的组数，分别为 4，2，1
                for (u = 0; u < n / 2; u++) {   // 对每组进行计算, a0 和 b0 的个数分别为 n/2
                    wu = -1 * 2 * M_PI * u / n; // 计算旋转因子
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  如果是傅里叶逆变换，此处 flag = -1

                    a0 = dst[y * NUM_x + k * n + u];         // 奇数项 	[y][k*n+u]
                    a1 = dst[y * NUM_x + k * n + u + n / 2]; // 偶数项 	[y][k*n+u+n/2]

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[y * NUM_x + k * n + u].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[y * NUM_x + k * n + u].y = a0.y + t.y;
                    dst[y * NUM_x + k * n + u + n / 2].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[y * NUM_x + k * n + u + n / 2].y = a0.y - t.y;
                }
            }
        }
        if (flag == 1) // 正向时，除一个X长度，避免数据过大，本来不应该除的
            for (u = 0; u < NUM_x; u++) {
                dst[y * NUM_x + u].x /= NUM_x;
                dst[y * NUM_x + u].y /= NUM_x;
            }
    }

    // 对y每一列做傅里叶变换
    for (x = 0; x < NUM_x; x++) {
        // 先分割数组
        split_array(&dst[0 * NUM_x + x], &dst[0 * NUM_x + x], 0, NUM_y, 1, NUM_y, NUM_x); // 对 y分组

        // 对 f[][x] 这一组数进行傅里叶变换
        for (i = 0; i < log(1.0 * NUM_y) / log(2.0); i++) { //计算次数为 2^n = num，即n = log2^num
            // 每次计算的间隔是 2^n,分别为 1，2，4，8
            n = 2 * pow(2.0, i);                // 本轮一组个数为 2 * 2^n，分别为 2,4,8,则好3轮
            for (k = 0; k < NUM_y / n; k++) {   // num/n 为当前的组数，分别为 4，2，1
                for (u = 0; u < n / 2; u++) {   // 对每组进行计算, a0 和 b0 的个数分别为 n/2
                    wu = -1 * 2 * M_PI * u / n; // 计算旋转因子
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  如果是傅里叶逆变换，此处 flag = -1

                    a0 = dst[(k * n + u) * NUM_x + x];         // 奇数项 	[k*n+u][x]
                    a1 = dst[(k * n + u + n / 2) * NUM_x + x]; // 偶数项 		[(k*n + u + n/2)*NUM_y 	+ x ][x]

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

    // 傅里叶正变换时，将四边平移到中心
    if (flag == 1)
        fft_shift(dst, NUM_y, NUM_x);

    // 打印当变换结果
    end = clock();
    printf("\n傅里叶%s变换结束，耗时%fs, NUM=%d x %d\n", flag == 1 ? "" : "逆", (double)(end - start) / CLOCKS_PER_SEC, NUM_x, NUM_y);
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
            t[i].x = s[i * 2 + 1].x; // 鏆傚瓨濂囨暟椤?
            t[i].y = s[i * 2 + 1].y;

            d[i].x = s[i * 2].x; // 鎷疯礉鍋舵暟椤瑰埌浣庝綅
            d[i].y = s[i * 2].y;
        }
        for (i = 0; i < x_n / 2; i++) {
            d[i + x_n / 2].x = t[i].x; // 鎷疯礉濂囨暟椤瑰埌楂樹綅
            d[i + x_n / 2].y = t[i].y;
        }
        split_array(dst, dst, x_n / 2, y_n, flag, NUM_y, NUM_x);
        split_array(dst + x_n / 2, dst + x_n / 2, x_n / 2, y_n, flag, NUM_y, NUM_x);
    } else {
        if (y_n <= 1) return;

        for (i = 0; i < y_n / 2; i++) {
            t[i].x = s[(i * 2 + 1) * NUM_x].x; // 鏆傚瓨濂囨暟椤?
            t[i].y = s[(i * 2 + 1) * NUM_x].y;

            d[i * NUM_x].x = s[(i * 2) * NUM_x].x; // 鎷疯礉鍋舵暟椤瑰埌浣庝綅
            d[i * NUM_x].y = s[(i * 2) * NUM_x].y;
        }
        for (i = 0; i < y_n / 2; i++) {
            d[(i + y_n / 2) * NUM_x].x = t[i].x; // 鎷疯礉濂囨暟椤瑰埌楂樹綅
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