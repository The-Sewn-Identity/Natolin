#ifndef LEVELS_H
#define LEVELS_H

#include <lslread.h>
#include "render.h"
#include "fields.h"

typedef struct Level {
    LSL_Layout lsl;
    LSL_Texture_Container lsl_tex;
    Fieldset fld;
} Level;

extern LSL_Layout PAX_Layout_01;
extern LSL_Texture_Container PAX_Container_01;
extern Fieldset PAX_Fieldset_01;

extern LSL_Layout * current_level;
extern LSL_Texture_Container * current_tex_cont;
extern Fieldset * current_fieldset;

void LoadLevels(void);
void LoadTextureContainers(void);
void LoadFieldsets(void);

#endif