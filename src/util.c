#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "colors.h"
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

void DrawField(Field *fld, Color col) {
    if (fld->point_arr.array != NULL) {

        Vector2 *point_arr = (Vector2*)fld->point_arr.array;
        int l = (fld->point_arr.size / sizeof(Vector2)) - 1;

        rlBegin(RL_TRIANGLES);
            for (int f = 0, m = 1; f < l; m = f++) {
                rlColor4ub(col.r, col.g, col.b, col.a);
                
                rlVertex2f(point_arr[f].x, point_arr[f].y);
                
                rlVertex2f(point_arr[m].x, point_arr[m].y);
                
                rlVertex2f(point_arr[l].x, point_arr[l].y);
            }
        rlEnd();
    }
}