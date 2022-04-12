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
    // 閸屽懘鍣烽崣鑸殿劀閸欐ɑ宕查弮璁圭礉鐏忓棔鑵戣箛鍐ㄩ挬缁夎鍩岄崶娑滅珶
    if (flag == -1)
        fft_shift(src, NUM_y, NUM_x);
    // 鐎电畧濮ｅ繋绔寸悰灞戒粵閸屽懘鍣烽崣璺哄綁閹癸拷
    for (y = 0; y < NUM_y; y++) {
        // 閸忓牆鍨庨崜鍙夋殶缂侊拷
        split_array(&src[y * NUM_x + 0], &dst[y * NUM_x + 0], NUM_x, 0, 0, NUM_y, NUM_x); // 鐎碉拷 x閸掑棛绮�

        // 鐎碉拷 f[y][] 鏉╂瑤绔寸紒鍕殶鏉╂稖顢戦崒鍛村櫡閸欒泛褰夐幑锟�
        for (i = 0; i < log(1.0 * NUM_x) / log(2.0); i++) { //鐠侊紕鐣诲▎鈩冩殶娑擄拷 2^n = num閿涘苯宓唍 = log2^num
            // 濮ｅ繑顐肩拋锛勭暬閻ㄥ嫰妫块梾鏃€妲� 2^n,閸掑棗鍩嗘稉锟� 1閿涳拷2閿涳拷4閿涳拷8
            n = 2 * pow(2.0, i);                // 閺堫剝鐤嗘稉鈧紒鍕嚋閺侀璐� 2 * 2^n閿涘苯鍨庨崚顐¤礋 2,4,8,閸掓瑥銈�3鏉烇拷
            for (k = 0; k < NUM_x / n; k++) {   // num/n 娑撳搫缍嬮崜宥囨畱缂佸嫭鏆熼敍灞藉瀻閸掝偂璐� 4閿涳拷2閿涳拷1
                for (u = 0; u < n / 2; u++) {   // 鐎佃鐦＄紒鍕箻鐞涘矁顓哥粻锟�, a0 閸滐拷 b0 閻ㄥ嫪閲滈弫鏉垮瀻閸掝偂璐� n/2
                    wu = -1 * 2 * M_PI * u / n; // 鐠侊紕鐣婚弮瀣祮閸ョ姴鐡�
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  婵″倹鐏夐弰顖氬€曢柌灞藉骄闁棗褰夐幑顫礉濮濄倕顦� flag = -1

                    a0 = dst[y * NUM_x + k * n + u];         // 婵傚洦鏆熸い锟� 	[y][k*n+u]
                    a1 = dst[y * NUM_x + k * n + u + n / 2]; // 閸嬭埖鏆熸い锟� 	[y][k*n+u+n/2]

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[y * NUM_x + k * n + u].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[y * NUM_x + k * n + u].y = a0.y + t.y;
                    dst[y * NUM_x + k * n + u + n / 2].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[y * NUM_x + k * n + u + n / 2].y = a0.y - t.y;
                }
            }
        }
        if (flag == 1) // 濮濓絽鎮滈弮璁圭礉闂勩倓绔存稉鐚夐梹鍨閿涘矂浼╅崗宥嗘殶閹诡喛绻冩径褝绱濋張顒佹降娑撳秴绨茬拠銉╂珟閻拷
            for (u = 0; u < NUM_x; u++) {
                dst[y * NUM_x + u].x /= NUM_x;
                dst[y * NUM_x + u].y /= NUM_x;
            }
    }

    // 鐎电畨濮ｅ繋绔撮崚妤€浠涢崒鍛村櫡閸欒泛褰夐幑锟�
    for (x = 0; x < NUM_x; x++) {
        // 閸忓牆鍨庨崜鍙夋殶缂侊拷
        split_array(&dst[0 * NUM_x + x], &dst[0 * NUM_x + x], 0, NUM_y, 1, NUM_y, NUM_x); // 鐎碉拷 y閸掑棛绮�

        // 鐎碉拷 f[][x] 鏉╂瑤绔寸紒鍕殶鏉╂稖顢戦崒鍛村櫡閸欒泛褰夐幑锟�
        for (i = 0; i < log(1.0 * NUM_y) / log(2.0); i++) { //鐠侊紕鐣诲▎鈩冩殶娑擄拷 2^n = num閿涘苯宓唍 = log2^num
            // 濮ｅ繑顐肩拋锛勭暬閻ㄥ嫰妫块梾鏃€妲� 2^n,閸掑棗鍩嗘稉锟� 1閿涳拷2閿涳拷4閿涳拷8
            n = 2 * pow(2.0, i);                // 閺堫剝鐤嗘稉鈧紒鍕嚋閺侀璐� 2 * 2^n閿涘苯鍨庨崚顐¤礋 2,4,8,閸掓瑥銈�3鏉烇拷
            for (k = 0; k < NUM_y / n; k++) {   // num/n 娑撳搫缍嬮崜宥囨畱缂佸嫭鏆熼敍灞藉瀻閸掝偂璐� 4閿涳拷2閿涳拷1
                for (u = 0; u < n / 2; u++) {   // 鐎佃鐦＄紒鍕箻鐞涘矁顓哥粻锟�, a0 閸滐拷 b0 閻ㄥ嫪閲滈弫鏉垮瀻閸掝偂璐� n/2
                    wu = -1 * 2 * M_PI * u / n; // 鐠侊紕鐣婚弮瀣祮閸ョ姴鐡�
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  婵″倹鐏夐弰顖氬€曢柌灞藉骄闁棗褰夐幑顫礉濮濄倕顦� flag = -1

                    a0 = dst[(k * n + u) * NUM_x + x];         // 婵傚洦鏆熸い锟� 	[k*n+u][x]
                    a1 = dst[(k * n + u + n / 2) * NUM_x + x]; // 閸嬭埖鏆熸い锟� 		[(k*n + u + n/2)*NUM_y 	+ x ][x]

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

    // 閸屽懘鍣烽崣鑸殿劀閸欐ɑ宕查弮璁圭礉鐏忓棗娲撴潏鐟伴挬缁夎鍩屾稉顓炵妇
    if (flag == 1)
        fft_shift(dst, NUM_y, NUM_x);

    // 閹垫挸宓冭ぐ鎾冲綁閹广垻绮ㄩ弸锟�
    end = clock();
    printf("\n閸屽懘鍣烽崣锟�%s閸欐ɑ宕茬紒鎾存将閿涘矁鈧妞�%fs, NUM=%d x %d\n", flag == 1 ? "" : "闁拷", (double)(end - start) / CLOCKS_PER_SEC, NUM_x, NUM_y);
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
            t[i].x = s[i * 2 + 1].x; // 闁哄棗鍊搁悺銊︾附閸ャ劍娈跺锟�?
            t[i].y = s[i * 2 + 1].y;

            d[i].x = s[i * 2].x; // 闁归鏌夌粈澶愬磻閼稿灚娈跺銈囨嚀閸╁本鎷呮惔婵堢Т
            d[i].y = s[i * 2].y;
        }
        for (i = 0; i < x_n / 2; i++) {
            d[i + x_n / 2].x = t[i].x; // 闁归鏌夌粈澶嬬附閸ャ劍娈跺銈囨嚀閸╁本顨囧Ο鍦Т
            d[i + x_n / 2].y = t[i].y;
        }
        split_array(dst, dst, x_n / 2, y_n, flag, NUM_y, NUM_x);
        split_array(dst + x_n / 2, dst + x_n / 2, x_n / 2, y_n, flag, NUM_y, NUM_x);
    } else {
        if (y_n <= 1) return;

        for (i = 0; i < y_n / 2; i++) {
            t[i].x = s[(i * 2 + 1) * NUM_x].x; // 闁哄棗鍊搁悺銊︾附閸ャ劍娈跺锟�?
            t[i].y = s[(i * 2 + 1) * NUM_x].y;

            d[i * NUM_x].x = s[(i * 2) * NUM_x].x; // 闁归鏌夌粈澶愬磻閼稿灚娈跺銈囨嚀閸╁本鎷呮惔婵堢Т
            d[i * NUM_x].y = s[(i * 2) * NUM_x].y;
        }
        for (i = 0; i < y_n / 2; i++) {
            d[(i + y_n / 2) * NUM_x].x = t[i].x; // 闁归鏌夌粈澶嬬附閸ャ劍娈跺銈囨嚀閸╁本顨囧Ο鍦Т
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