#include <raylib.h>
#include <stdio.h>
#include "util.h"

int rhlval(int n1, int n2, char op) {
    int retval;

    if (op == '>') {
        retval = (n1 > n2) ? n1 : n2;
    } else if (op == '<') {
        retval = (n1 < n2) ? n1 : n2;
    } else {
        retval = 0;
    }
    return retval;
}