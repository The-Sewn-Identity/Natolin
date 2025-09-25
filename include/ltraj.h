#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>
#include <stdint.h>

typedef struct Trajectory {
    Vector2 * vect_arr;
    uint16_t layer;
    uint16_t count;
} Trajectory;

typedef Trajectory * TrajLayout;

TrajLayout LoadTrajFile(char * filename);

#endif