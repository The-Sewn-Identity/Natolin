#ifndef LTRAJ_H
#define LTRAJ_H

#include <raylib.h>
#include <stdint.h>
#include "util.h"

typedef struct Trajectory {
    Vector2 * vect_arr;
    uint16_t layer;
    uint16_t count;
} Trajectory;

// trzeba to zmienić

typedef struct Field {
    r_array point_arr;
    uint16_t layer;
} Field;

typedef Trajectory * TrajLayout;
typedef Field * Fieldset;

TrajLayout LoadTrajFile(char * filename);
Fieldset LoadFieldset(char * filename);

#endif