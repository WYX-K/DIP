#include <stdio.h>
#include "func.c"
#include "funcdef.h"

int main() {
    char *input = "..\\images\\lena.pgm";
    char *output = "..\\output\\lena.pgm";

    ChangeImage(input, output);

    return 0;
}