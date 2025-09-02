#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>

typedef struct Trajectory {
    unsigned short int layer;
    Vector2 vect[];
} Trajectory;

typedef Trajectory * TrajLayout;

TrajLayout LoadTrajFile(char * filename);

#endif