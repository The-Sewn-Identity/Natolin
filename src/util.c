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

Vector2 VectOperation(Vector2 vector, float factor, char op) {
    Vector2 vect = vector;
    if (factor == 0) { factor++; }
    switch (op) {
        case '+':
            vect.x += factor; vect.y += factor;
            break;
        case '-':
            vect.x -= factor; vect.y -= factor;
            break;
        case '*':
            vect.x *= factor; vect.y *= factor;
            break;
        case '/':
            vect.x /= factor; vect.y /= factor;
            break;
        default:
            break;
    }
    return vect;
}