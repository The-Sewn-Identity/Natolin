#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
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

void *nalloc(void *__ptr, size_t __size) {
    int *nptr; nptr = realloc(__ptr, __size);
    if (nptr != NULL) { __ptr = nptr; }
    return __ptr;
}