#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>

typedef struct TrajVector {
    float result;
    float x;
    float y;
} TrajVector;

typedef struct Trajectory {
    unsigned short layer;
    TrajVector vect_arr[16];
} Trajectory;

typedef Trajectory * TrajLayout;

TrajLayout LoadTrajFile(char * filename);

#endif