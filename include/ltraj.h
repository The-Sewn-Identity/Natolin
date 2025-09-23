#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>

typedef struct Trajectory {
    Vector2 * vect_arr;
    unsigned short layer;
    unsigned short count;
} Trajectory;

typedef Trajectory * TrajLayout;

TrajLayout LoadTrajFile(char * filename);

#endif