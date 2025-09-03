#ifndef LEVELS_H
#define LEVELS_H

#include <lslread.h>
#include "render.h"

extern LSL_Layout PAX_Congress;
extern LSL_Texture_Container PAX_Container_01;

extern LSL_Layout * current_level;
extern LSL_Texture_Container * current_tex_cont;

void LoadLevels(void);
void LoadTextureContainers(void);
void LoadTrajectories(void);

#endif