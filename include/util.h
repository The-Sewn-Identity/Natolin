#ifndef UTIL_H
#define UTIL_H

#include <math.h>

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])
#define FREEPTR(ptr) (free(ptr), ptr = NULL)
#define PYTHAGORAS(s1, s2) ( sqrtf(powf(s1, 2) + powf(s2, 2)) )

#define WITHIN(l1, l2, l3) ({ (l1 < l2) ? ((l3 > l1 && l3 <= l2) ? true : false) : ((l3 > l2 && l3 <= l1) ? true : false); })
int rhlval(int n1, int n2, char op);
void *nalloc(void *__ptr, size_t __size);

enum _RL_types {
    TYPE_TEXTURE2D = 192,
    TYPE_TEXTURE2D_PTR = 193
};

#define string_eq(str1, str2) ((strcmp(str1, str2) == 0) ? 1 : 0)
#define typeof(x) (_Generic((x), Texture2D : TYPE_TEXTURE2D, Texture2D * : TYPE_TEXTURE2D_PTR, default : 0))

#endif