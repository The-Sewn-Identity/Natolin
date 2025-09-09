#ifndef LEVELS_H
#define LEVELS_H

#include <lslread.h>
#include "render.h"
#include "ltraj.h"

extern LSL_Layout PAX_Congress;
extern LSL_Texture_Container PAX_Container_01;
extern TrajLayout PAX_Trajectory_01;

extern LSL_Layout * current_level;
extern LSL_Texture_Container * current_tex_cont;
extern TrajLayout * current_traject;

void LoadLevels(void);
void LoadTextureContainers(void);
void LoadTrajectories(void);

#endif