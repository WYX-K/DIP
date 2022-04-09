unsigned char *Normal(double *arr_in, int size, int range) {
    double max = 0, min = range, temp;
    int i;
    unsigned char *arr_out = (unsigned char *)malloc(sizeof(char) * size);

    for (i = 0; i < size; ++i) {
        temp = arr_in[i];
        if (temp > max) max = temp;
        if (temp < min) min = temp;
    }

    for (i = 0; i < size; ++i)
        arr_out[i] = (int)log(((arr_in[i] - min) / (max - min) * range) + 1) * 20;
    return arr_out;
}

void fft(struct _complex *src, struct _complex *dst, int flag, int height, int width) {
    int y, x, i, u, k, n;
    int NUM_y = 256, NUM_x = 256;
    double wu;
    struct _complex w, a0, a1, t;
    clock_t start, end;
    start = clock();

    if (flag == -1)
        fft_shift(src, NUM_y, NUM_x);

    for (y = 0; y < NUM_y; y++) {
        split_array(&src[y * NUM_x + 0], &dst[y * NUM_x + 0], NUM_x, 0, 0, NUM_y, NUM_x);

        for (i = 0; i < log(1.0 * NUM_x) / log(2.0); i++) {
            n = 2 * pow(2.0, i);
            for (k = 0; k < NUM_x / n; k++) {
                for (u = 0; u < n / 2; u++) {
                    wu = -1 * 2 * M_PI * u / n;
                    w.x = cos(wu);
                    w.y = flag * sin(wu);

                    a0 = dst[y * NUM_x + k * n + u];
                    a1 = dst[y * NUM_x + k * n + u + n / 2];

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[y * NUM_x + k * n + u].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[y * NUM_x + k * n + u].y = a0.y + t.y;
                    dst[y * NUM_x + k * n + u + n / 2].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[y * NUM_x + k * n + u + n / 2].y = a0.y - t.y;
                }
            }
        }
        if (flag == 1)
            for (u = 0; u < NUM_x; u++) {
                dst[y * NUM_x + u].x /= NUM_x;
                dst[y * NUM_x + u].y /= NUM_x;
            }
    }

    for (x = 0; x < NUM_x; x++) {
        split_array(&dst[0 * NUM_x + x], &dst[0 * NUM_x + x], 0, NUM_y, 1, NUM_y, NUM_x);

        for (i = 0; i < log(1.0 * NUM_y) / log(2.0); i++) {
            n = 2 * pow(2.0, i);
            for (k = 0; k < NUM_y / n; k++) {
                for (u = 0; u < n / 2; u++) {
                    wu = -1 * 2 * M_PI * u / n;
                    w.x = cos(wu);
                    w.y = flag * sin(wu); // flag = -1

                    a0 = dst[(k * n + u) * NUM_x + x];         // [k*n+u][x]
                    a1 = dst[(k * n + u + n / 2) * NUM_x + x]; // [(k*n + u + n/2)*NUM_y 	+ x ][x]

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

    if (flag == 1)
        fft_shift(dst, NUM_y, NUM_x);

    end = clock();
    printf("%s,TIME:%fs, SIZE=%d x %d\n", flag == 1 ? "FFI" : "IFFT", (double)(end - start) / CLOCKS_PER_SEC, NUM_x, NUM_y);
}

double *getResult(struct _complex *src, int size) {
    int i;
    double *res = (double *)malloc(sizeof(double) * size);

    for (i = 0; i < size; ++i)
        res[i] = 1 + sqrt(src[i].x * src[i].x + src[i].y * src[i].y);

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
            t[i].x = s[i * 2 + 1].x; // 閺嗗倸鐡ㄦ總鍥ㄦ殶閿燂拷?
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
            t[i].x = s[(i * 2 + 1) * NUM_x].x; // 閺嗗倸鐡ㄦ總鍥ㄦ殶閿燂拷?
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