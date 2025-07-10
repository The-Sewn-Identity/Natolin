#include <stdio.h>
#include <lslread.h>
#include "levels.h"

LSL_Layout PAX_Congress;
LSL_Texture_Container PAX_Container_01;

LSL_Layout * current_level;
LSL_Texture_Container * current_tex_cont;

void LoadLevels(void) {
    PAX_Congress = ReadMap("assets/levels/PAX_Congress.lsl");

    current_level = &PAX_Congress;
}

void LoadTextureContainers(void) {
    CreateLSLTexCont(PAX_Container_01, PAX_Congress);

    current_tex_cont = &PAX_Container_01;
}