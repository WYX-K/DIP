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
    // 闂佺ǹ鑻幊姗€宕抽悜钘夌煑闁煎憡顔栭崝鈧梺鍛婄懄钃辩€规洘鐓″顔炬媼閸︻厾顦柣蹇撶箰濡棃鎳欓幋锝囩杸闁告劑鍔戦幐顒傜磼婢跺寒鍤欓柛鈺佺焸瀹曡泛鈽夊⿰鍛骄
    if (flag == -1)
        fft_shift(src, NUM_y, NUM_x);
    // 闁诲海鏁搁悾褎鎱ㄩ敐鍛缂佹柨顕幃鎵沪閹存帞椹抽梺绋胯嫰閹虫﹢宕抽悜钘夌煑閻犲搫鎼紞渚€鏌熼惂鍛婂
    for (y = 0; y < NUM_y; y++) {
        // 闂佺ǹ绻愰悧鍡涘垂鎼淬劌绀堥柛娆忣槹濞堝墎绱撴笟濠冨
        split_array(&src[y * NUM_x + 0], &dst[y * NUM_x + 0], NUM_x, 0, 0, NUM_y, NUM_x); // 闁诲海顣幏锟� x闂佸憡甯掑Λ娑氬垝閿燂拷

        // 闁诲海顣幏锟� f[y][] 闁哄鏅滈悷銈囩博鐎靛摜纾奸柛鏇ㄥ墯濞堝爼寮堕埡鍌滎灱妞ゃ垺鍨垮畷鎺楀川閺夋垶顏為梺鍛婄懆濞夋稖銇愭径鎰闁跨噦鎷�
        for (i = 0; i < log(1.0 * NUM_x) / log(2.0); i++) { //闁荤姳绶ょ槐鏇㈡偩鐠囨祴鏋庨柍鈺佸暞濞堣泛鈽夐幙鍕 2^n = num闂佹寧绋戦懟顖氱暤閸烇拷 = log2^num
            // 濠殿噯绲界换鎴︻敃閼测晜濯奸柨娑樺閺嗩剟鏌ｉ妸銉ヮ伃婵☆偄娼″楣冨籍閳ь剙危閿燂拷 2^n,闂佸憡甯掑Λ妤呭春閸℃鈻旈柨鐕傛嫹 1闂佹寧鍐婚幏锟�2闂佹寧鍐婚幏锟�4闂佹寧鍐婚幏锟�8
            n = 2 * pow(2.0, i);                // 闂佸搫鐗滈崜婵嬫偪閸℃鈻旈柍褜鍓涚槐鎺楀礋椤忓牆娈濋梺杞扮窔椤ｏ妇鎷归敓锟� 2 * 2^n闂佹寧绋戦懟顖炲垂鎼淬劌绀嗘い鎯点倗顦� 2,4,8,闂佸憡甯楅悷銉╁Χ閿燂拷3闁哄鍎戦幏锟�
            for (k = 0; k < NUM_x / n; k++) {   // num/n 婵炴垶鎸搁幖顐ょ礊鐎ｎ喖绀堢€广儱娲﹂悾杈╃磽娴ｇǹ顏柡鍡欏枛閺佸秶浠﹂挊澶屸偓濠氭煕閹烘繂浜楅悹鎰舵嫹 4闂佹寧鍐婚幏锟�2闂佹寧鍐婚幏锟�1
                for (u = 0; u < n / 2; u++) {   // 闁诲簼绲婚～澶愭儊閿涘嫮纾奸柛鏇ㄥ枤缁犲鎮跺☉妯肩劮妞ゆ挸鎽滅划濠氭晸閿燂拷, a0 闂佸憡绮ｉ幏锟� b0 闂佹眹鍔岀€氼亪鏌屽⿰鍫濇瀬闁哄鐏濋悗濠氭煕閹烘繂浜楅悹鎰舵嫹 n/2
                    wu = -1 * 2 * M_PI * u / n; // 闁荤姳绶ょ槐鏇㈡偩婵犳艾绫嶉悗锝庡幗缁侇噣鏌涢妷褍孝闁烩槄鎷�
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  婵犵鈧啿鈧綊鎮樻径鎰強妞ゆ牗鑹鹃埀顒佹礋閺屽瞼浠﹂挊澶愮崕闂備緡鍋勫Λ妤勩亹婢舵劕绠叉い顐枤缁€澶嬫叏濠靛嫬鈧洟藝閿燂拷 flag = -1

                    a0 = dst[y * NUM_x + k * n + u];         // 婵犻潧鍊稿ú锕傚汲閻旀悶浜滈柨鐕傛嫹 	[y][k*n+u]
                    a1 = dst[y * NUM_x + k * n + u + n / 2]; // 闂佺ǹ顑堥崺鏍汲閻旀悶浜滈柨鐕傛嫹 	[y][k*n+u+n/2]

                    t.x = w.x * a1.x - w.y * a1.y;
                    t.y = w.x * a1.y + w.y * a1.x;

                    dst[y * NUM_x + k * n + u].x = a0.x + t.x; // F[u] = A0 + wA1
                    dst[y * NUM_x + k * n + u].y = a0.y + t.y;
                    dst[y * NUM_x + k * n + u + n / 2].x = a0.x - t.x; // F[u+n/2] = A0 - wA1
                    dst[y * NUM_x + k * n + u + n / 2].y = a0.y - t.y;
                }
            }
        }
        if (flag == 1) // 濠殿喗绻愮徊浠嬪箖濠婂牆绫嶉悹浣告贡缁€澶愭⒒閸曗晛鈧挾绮╃€涙鈻旈柣姘樀濮婂綊宕归纰卞敽闂佹寧绋戦惌鍌涘閳哄懎绀傜€广儱妫欏▓鍫曟煙鐠団€虫灕缂佽鍟鍕檪缂佽鲸绻堝鐢割敆娴ｅ綊妾锋繛鎴炴尭缁夊鑺遍懠顒佸珰闁靛鏅滈悵鐔兼煟椤帗瀚�
            for (u = 0; u < NUM_x; u++) {
                dst[y * NUM_x + u].x /= NUM_x;
                dst[y * NUM_x + u].y /= NUM_x;
            }
    }

    // 闁诲海鏁搁悾銊︽叏閿濆懐绠ｇ紒鏃€鎸冲畷姘旈埀顒佺濞戙垹纾奸柛娑欐綑濞咃繝鏌涘▎鎺撶【鐟滄澘顦甸獮鎴︽晸閿燂拷
    for (x = 0; x < NUM_x; x++) {
        // 闂佺ǹ绻愰悧鍡涘垂鎼淬劌绀堥柛娆忣槹濞堝墎绱撴笟濠冨
        split_array(&dst[0 * NUM_x + x], &dst[0 * NUM_x + x], 0, NUM_y, 1, NUM_y, NUM_x); // 闁诲海顣幏锟� y闂佸憡甯掑Λ娑氬垝閿燂拷

        // 闁诲海顣幏锟� f[][x] 闁哄鏅滈悷銈囩博鐎靛摜纾奸柛鏇ㄥ墯濞堝爼寮堕埡鍌滎灱妞ゃ垺鍨垮畷鎺楀川閺夋垶顏為梺鍛婄懆濞夋稖銇愭径鎰闁跨噦鎷�
        for (i = 0; i < log(1.0 * NUM_y) / log(2.0); i++) { //闁荤姳绶ょ槐鏇㈡偩鐠囨祴鏋庨柍鈺佸暞濞堣泛鈽夐幙鍕 2^n = num闂佹寧绋戦懟顖氱暤閸烇拷 = log2^num
            // 濠殿噯绲界换鎴︻敃閼测晜濯奸柨娑樺閺嗩剟鏌ｉ妸銉ヮ伃婵☆偄娼″楣冨籍閳ь剙危閿燂拷 2^n,闂佸憡甯掑Λ妤呭春閸℃鈻旈柨鐕傛嫹 1闂佹寧鍐婚幏锟�2闂佹寧鍐婚幏锟�4闂佹寧鍐婚幏锟�8
            n = 2 * pow(2.0, i);                // 闂佸搫鐗滈崜婵嬫偪閸℃鈻旈柍褜鍓涚槐鎺楀礋椤忓牆娈濋梺杞扮窔椤ｏ妇鎷归敓锟� 2 * 2^n闂佹寧绋戦懟顖炲垂鎼淬劌绀嗘い鎯点倗顦� 2,4,8,闂佸憡甯楅悷銉╁Χ閿燂拷3闁哄鍎戦幏锟�
            for (k = 0; k < NUM_y / n; k++) {   // num/n 婵炴垶鎸搁幖顐ょ礊鐎ｎ喖绀堢€广儱娲﹂悾杈╃磽娴ｇǹ顏柡鍡欏枛閺佸秶浠﹂挊澶屸偓濠氭煕閹烘繂浜楅悹鎰舵嫹 4闂佹寧鍐婚幏锟�2闂佹寧鍐婚幏锟�1
                for (u = 0; u < n / 2; u++) {   // 闁诲簼绲婚～澶愭儊閿涘嫮纾奸柛鏇ㄥ枤缁犲鎮跺☉妯肩劮妞ゆ挸鎽滅划濠氭晸閿燂拷, a0 闂佸憡绮ｉ幏锟� b0 闂佹眹鍔岀€氼亪鏌屽⿰鍫濇瀬闁哄鐏濋悗濠氭煕閹烘繂浜楅悹鎰舵嫹 n/2
                    wu = -1 * 2 * M_PI * u / n; // 闁荤姳绶ょ槐鏇㈡偩婵犳艾绫嶉悗锝庡幗缁侇噣鏌涢妷褍孝闁烩槄鎷�
                    w.x = cos(wu);
                    w.y = flag * sin(wu); //  婵犵鈧啿鈧綊鎮樻径鎰強妞ゆ牗鑹鹃埀顒佹礋閺屽瞼浠﹂挊澶愮崕闂備緡鍋勫Λ妤勩亹婢舵劕绠叉い顐枤缁€澶嬫叏濠靛嫬鈧洟藝閿燂拷 flag = -1

                    a0 = dst[(k * n + u) * NUM_x + x];         // 婵犻潧鍊稿ú锕傚汲閻旀悶浜滈柨鐕傛嫹 	[k*n+u][x]
                    a1 = dst[(k * n + u + n / 2) * NUM_x + x]; // 闂佺ǹ顑堥崺鏍汲閻旀悶浜滈柨鐕傛嫹 		[(k*n + u + n/2)*NUM_y 	+ x ][x]

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

    // 闂佺ǹ鑻幊姗€宕抽悜钘夌煑闁煎憡顔栭崝鈧梺鍛婄懄钃辩€规洘鐓″顔炬媼閸︻厾顦柣蹇撶箰濡煤閹惧瓨缍囬柣鐔跺嵆閹割剛绱掓径搴殭闁糕晛鏈粙澶愵敇閻愰潧顩�
    if (flag == 1)
        fft_shift(dst, NUM_y, NUM_x);

    // 闂佺懓鐏氶幐绋跨暤閸愵厹浜归柟鎯у暱缂嶄線鏌熼獮鍨伄缂侇喓鍔戝鎼佹晸閿燂拷
    end = clock();
    printf("\n闂佺ǹ鑻幊姗€宕抽悜钘夌煑闁跨噦鎷�%s闂佸憡鐟﹁摫鐎规洝灏欑槐鎺楀箻鐎涙ê鐨㈤梺鎸庣☉閻線鍩€椤掍緡娈曟俊鐑囨嫹%fs, NUM=%d x %d\n", flag == 1 ? "" : "闂備緡鍋撻幏锟�", (double)(end - start) / CLOCKS_PER_SEC, NUM_x, NUM_y);
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
            t[i].x = s[i * 2 + 1].x; // 闂備礁鎼Λ妤呭磹閹间焦鍋ら柕濠忓闂勫嫰鏌涢妷锝呭婵炲牐娉涢—鍐晸閿燂拷?
            t[i].y = s[i * 2 + 1].y;

            d[i].x = s[i * 2].x; // 闂備礁缍婇ˉ鎾诲蓟婢跺瞼鐭嗗鑸靛姇绾惧鏌ょ粙璺ㄤ粵婵炲牐娉涢—鍐Χ閸ャ劌娈岄梺绯曟櫅閺堫剟骞忛崨顔藉劅婵犻潧鐗忓瓭
            d[i].y = s[i * 2].y;
        }
        for (i = 0; i < x_n / 2; i++) {
            d[i + x_n / 2].x = t[i].x; // 闂備礁缍婇ˉ鎾诲蓟婢跺瞼鐭嗗璺侯儑闂勫嫰鏌涢妷锝呭婵炲牐娉涢—鍐Χ閸ャ劌娈岄梺绯曟櫅閺堫剟銆冮崶顬喖宕烽鐘橈拷
            d[i + x_n / 2].y = t[i].y;
        }
        split_array(dst, dst, x_n / 2, y_n, flag, NUM_y, NUM_x);
        split_array(dst + x_n / 2, dst + x_n / 2, x_n / 2, y_n, flag, NUM_y, NUM_x);
    } else {
        if (y_n <= 1) return;

        for (i = 0; i < y_n / 2; i++) {
            t[i].x = s[(i * 2 + 1) * NUM_x].x; // 闂備礁鎼Λ妤呭磹閹间焦鍋ら柕濠忓闂勫嫰鏌涢妷锝呭婵炲牐娉涢—鍐晸閿燂拷?
            t[i].y = s[(i * 2 + 1) * NUM_x].y;

            d[i * NUM_x].x = s[(i * 2) * NUM_x].x; // 闂備礁缍婇ˉ鎾诲蓟婢跺瞼鐭嗗鑸靛姇绾惧鏌ょ粙璺ㄤ粵婵炲牐娉涢—鍐Χ閸ャ劌娈岄梺绯曟櫅閺堫剟骞忛崨顔藉劅婵犻潧鐗忓瓭
            d[i * NUM_x].y = s[(i * 2) * NUM_x].y;
        }
        for (i = 0; i < y_n / 2; i++) {
            d[(i + y_n / 2) * NUM_x].x = t[i].x; // 闂備礁缍婇ˉ鎾诲蓟婢跺瞼鐭嗗璺侯儑闂勫嫰鏌涢妷锝呭婵炲牐娉涢—鍐Χ閸ャ劌娈岄梺绯曟櫅閺堫剟銆冮崶顬喖宕烽鐘橈拷
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