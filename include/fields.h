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
    float x_len; float y_len;
    uint8_t fieldcount;
} Fieldset;

Fieldset LoadFieldset(char * filename);
Vector2 AddCenterToField(Field *fld);

#endif