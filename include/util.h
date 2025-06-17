#ifndef UTIL_H
#define UTIL_H

#define ARRAYSIZE(arr, type) sizeof(arr) / sizeof(type)
#define FREEPTR(ptr) (free(ptr), ptr = NULL)

#endif