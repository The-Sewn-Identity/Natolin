#include <raylib.h>
#include <raymath.h>
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

void DrawField(Field *fld) {
    Vector2 *points = fld->point_arr.array;
    Vector2 center = fld->center;

    if (points != NULL) {
        
    }
}