#ifndef UTIL_H
#define UTIL_H

#include <math.h>

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])
#define FREEPTR(ptr) (free(ptr), ptr = NULL)
#define PYTHAGORAS(s1, s2) ( sqrtf(pow(s1, 2) + pow(s2, 2)) )
//#define RADTOANG(angle) (angle * 180.0f / PI)

#endif