#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <lslread.h>
#include "util.h"
#include "levels.h"
#include "render.h"

LSL_Texture_Container * CreateLSLTextCont(LSL_Layout * layout) {
    LSL_Texture_Container * cont = malloc(sizeof(LSL_Texture_Container));
    for (int t=0; t < 64; t++) {
        for (int e=0; t < 128; e++) {
            *cont[t][e] = LoadTexture(
                TextFormat("assets/textures/levels/%s/%s.png", layout->levelname, layout->layers[t][e].image)
            );
        }
    }
    return cont;
}

void FreeLSLTextCont(LSL_Texture_Container * tex_cont) {
    for (int t=0; t < 64; t++) {
        for (int e=0; t < 128; e++) {
            UnloadTexture(*tex_cont[t][e]);
        }
    }
    FREEPTR(tex_cont);
}

void RenderLSL(LSL_Texture_Container * tex_cont) {
    LSL_Texture_Container *map = tex_cont;
}