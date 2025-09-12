#ifndef UTIL_H
#define UTIL_H

#include <math.h>

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])
#define FREEPTR(ptr) (free(ptr), ptr = NULL)
#define PYTHAGORAS(s1, s2) ( sqrtf(powf(s1, 2) + powf(s2, 2)) )

#define LOCCMP(l1, l2, l3) ({ int _max = (l1 < l2) ? l2 : l1; int _min = !_max; (l3 < _max && l3 > _min) ? true : false; })
//( ((int)(l1 - l3) | (int)(l1 - l3)) >= 0 ? true : false)
//#define RADTOANG(angle) (angle * 180.0f / PI)

#endif