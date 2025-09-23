#include <raylib.h>
#include <stdio.h>
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