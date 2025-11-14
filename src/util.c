#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "util.h"

int rhlval(int n1, int n2, char op) {
    switch (op) {
        case '>':
            return (n1 > n2) ? n1 : n2;
        case '<':
            return (n1 < n2) ? n1 : n2;
        default:
            return 0;
    }
}

// polygon qsort func
int cmpx(const void *x1, const void *x2) {
    return (*(float*)x1 - *(float*)x2);
}

int cmpy(const void *y1, const void *y2) {
    return (*(float*)y1 - *(float*)y2);
}

Vector2 AddCenterToField(Field *field) {
    Vector2 vect = { 0, 0 };

    if (field->point_arr.array != NULL) {
        const size_t length = field->point_arr.size / sizeof(Vector2);
        float x_arr[length]; float y_arr[length];

        for (int f=0; f < length; f++) {
            x_arr[f] = ((Vector2*)field->point_arr.array)[f].x;
            y_arr[f] = ((Vector2*)field->point_arr.array)[f].y;
        }

        qsort(x_arr, length, sizeof(float), cmpx);
        qsort(y_arr, length, sizeof(float), cmpy);

        float cx = x_arr[length-1] - x_arr[0];
        float cy = y_arr[length-1] - y_arr[0];

        vect = (Vector2){ x_arr[0] + cx/2, y_arr[0] + cy/2 };
    }
    return vect;
}