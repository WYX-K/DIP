#include <stdio.h>
#include "func.c"

int main() {
    char *input1 = "..\\images\\lena.pgm";
    char *output1 = "..\\output\\lena_averFilte.pgm";

    AverFilter(input1, output1, 3, 3);

    // char *output2 = "..\\output\\lena_midFilter.pgm";

    // MidFilter(input1, output2, 3, 3);

    // char *input2 = "..\\images\\noise.pgm";
    // char *output3 = "..\\output\\noise_averFilter.pgm";

    // AverFilter(input1, output1, 3, 3);

    // char *output4 = "..\\output\\noise_midFilter.pgm";

    // MidFilter(input1, output2, 3, 3);

    return 0;
}
