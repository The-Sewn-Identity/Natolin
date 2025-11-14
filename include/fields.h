#ifndef FIELDS_H
#define FIELDS_H

#include <raylib.h>
#include <stdint.h>
#include <extutil.h>

typedef struct Field {
    r_array point_arr;
    Vector2 center;
    uint8_t layer;
} Field;

typedef struct Fieldset {
    Field *field_arr;
    uint8_t fieldcount;
} Fieldset;

Fieldset LoadFieldset(char * filename);

#endif