#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stddef.h>
#include "fields.h"

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])
#define FREEPTR(ptr) (free(ptr), ptr = NULL)
#define PYTHAGORAS(s1, s2) ( sqrtf(powf(s1, 2) + powf(s2, 2)) )

#define WITHIN(l1, l2, l3) ({ (l1 < l2) ? ((l3 > l1 && l3 <= l2) ? true : false) : ((l3 > l2 && l3 <= l1) ? true : false); })
#define COUNTDIGITS(x) (int)((x == 0) ? 1 : log10f(abs(x)) + 1)
int rhlval(int n1, int n2, char op);
int cmpx(const void *x1, const void *x2);
int cmpy(const void *y1, const void *y2);

void DrawField(Field *fld);

enum _basic_types {
    TYPE_DEFAULT = 0,
    TYPE_INT,
    TYPE_CHAR,
};
enum _RL_types {
    TYPE_TEXTURE2D = 192,
    TYPE_TEXTURE2D_PTR = 193
};
enum _custom_types {
    TYPE_R_ARRAY = 576
};

#define string_eq(str1, str2) ((strcmp(str1, str2) == 0) ? 1 : 0)
#define typeof(x) (_Generic((x), \
    Texture2D : TYPE_TEXTURE2D, \
    Texture2D * : TYPE_TEXTURE2D_PTR, \
    r_array : TYPE_R_ARRAY \
    default : TYPE_DEFAULT \
))

#endif