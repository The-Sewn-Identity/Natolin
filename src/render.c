#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <lslread.h>
#include "util.h"
#include "levels.h"
#include "player.h"
#include "render.h"

void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout) {
    for (int o=0; o < 16; o++) {
        for (int r=0; r < 64; r++) {
            if (strcmp(layout.layers[o][r].image, "") != 0) {
                tex_cont[o][r].index = layout.layers[o][r].index;
                tex_cont[o][r].tex = LoadTexture(
                    TextFormat("assets/textures/levels/%s/%s.png", layout.levelname, layout.layers[o][r].image)
                );
                tex_cont[o][r].x_pos = layout.layers[o][r].x_pos;
                tex_cont[o][r].y_pos = layout.layers[o][r].y_pos;
                tex_cont[o][r].rect = (Rectangle){
                    tex_cont[o][r].x_pos, tex_cont[o][r].y_pos,
                    tex_cont[o][r].tex.width, tex_cont[o][r].tex.height};
                snprintf(tex_cont[o][r].feature, sizeof(layout.layers[o][r].feature), layout.layers[o][r].feature);
            }
            else {
                tex_cont[o][r] = (TextureDef){};
            }
            // printf("{%d, %d, %d, %d, %s}", tex_cont[o][r].index, tex_cont[o][r].tex.width, tex_cont[o][r].x_pos, tex_cont[o][r].y_pos, tex_cont[o][r].feature);
        }
    }
}

void FreeLSLTextCont(LSL_Texture_Container tex_cont) {
    for (int f=0; f < 16; f++) {
        for (int r=0; r < 64; r++) {
            UnloadTexture(tex_cont[f][r].tex);
        }
    }
}

void RenderLSL(LSL_Texture_Container tex_cont) {
    for (int r=0; r < 16; r++) {
        for (int e=0; e < 64; e++) {
            if (IsTextureValid(tex_cont[r][e].tex)) { 
                DrawTexture(tex_cont[r][e].tex, 
                    tex_cont[r][e].x_pos,
                    tex_cont[r][e].y_pos,
                    WHITE); 
            }
        }
    }
}