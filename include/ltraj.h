#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>

typedef struct Trajectory {
    unsigned short layer;
    unsigned short count;
    Vector2 * vect_arr;
} Trajectory;

typedef Trajectory * TrajLayout;

TrajLayout LoadTrajFile(char * filename);

#endif