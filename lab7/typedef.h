/*
 * @Author: WYX
 * @ID: 1930026123
 * @Date: 2022-03-08 14:42:43
 * @LastEditTime: 2022-03-08 20:34:35
 * @Description: file content
 */
#pragma once
#pragma once

#define GRAY 1
#define COLOR 2
#define PI 3.14159265
typedef struct Image {
    int Width;
    int Height;
    int Type; // Gray=1, Color=2;
    unsigned char *data;
    char comments[15][100];
    int num_comment_lines;
} Image;
