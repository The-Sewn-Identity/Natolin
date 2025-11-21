#include <stdio.h>
#include <lslread.h>
#include "levels.h"
#include "util.h"

LSL_Layout PAX_Layout_01;
LSL_Texture_Container PAX_Container_01;
Fieldset PAX_Fieldset_01;

LSL_Layout * current_level;
LSL_Texture_Container * current_tex_cont;
Fieldset * current_fieldset;


void LoadLevels(void) {
    PAX_Layout_01 = ReadMap("assets/levels/PAX_Congress.lsl");

    current_level = &PAX_Layout_01;
}

void LoadTextureContainers(void) {
    CreateLSLTexCont(PAX_Container_01, PAX_Layout_01);

    current_tex_cont = &PAX_Container_01;
}

void LoadFieldsets(void) {
    PAX_Fieldset_01 = LoadFieldset("assets/levels/PAX_Congress.fld");
    current_fieldset = &PAX_Fieldset_01;
}