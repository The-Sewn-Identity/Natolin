#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <lslread.h>
#include "util.h"
#include "levels.h"
#include "player.h"
#include "render.h"

void Open(TextureDef * texdef) {
}

void NextLevel(TextureDef * texdef) {
}

void DefaultFunc(TextureDef * texdef) {
}

void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout) {
    for (int o=0; o < 16; o++) {
        for (int r=0; r < 64; r++) {
            if (strcmp(layout.layers[o][r].image, "") != 0) {
                tex_cont[o][r].index = layout.layers[o][r].index;
                tex_cont[o][r].x_pos = layout.layers[o][r].x_pos; tex_cont[o][r].y_pos = layout.layers[o][r].y_pos;
                tex_cont[o][r].rect = (Rectangle){
                    tex_cont[o][r].x_pos, tex_cont[o][r].y_pos,
                    tex_cont[o][r].tex.width, tex_cont[o][r].tex.height
                };
                tex_cont[o][r].name = layout.layers[o][r].image;
                
                if (strcmp(layout.layers[o][r].feature, "OPEN") == 0) {
                    tex_cont[o][r].feature = Open;
                    tex_cont[o][r].tex_arr = malloc(2 * sizeof(Texture2D));

                    tex_cont[o][r].tex_arr[DEFAULT] = LoadTexture("assets/textures/levels/%s/%s.png");
                    tex_cont[o][r].tex_arr[OPEN] = LoadTexture("assets/textures/levels/%s/%s_open.png");
                    
                } else if (strcmp(layout.layers[o][r].feature, "NEXT__LVL") == 0) {
                    tex_cont[o][r].feature = NextLevel;
                } else if (strcmp(layout.layers[o][r].feature, "NONE") == 0) {
                    tex_cont[o][r].tex = LoadTexture(
                        TextFormat("assets/textures/levels/%s/%s.png", layout.levelname, layout.layers[o][r].image)
                    );
                    tex_cont[o][r].feature = DefaultFunc;
                } else {
                    tex_cont[o][r].feature = NULL;
                    tex_cont[o][r].tex = (Texture2D){};
                }
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

void RenderLevel(LSL_Texture_Container tex_cont) {
    for (int r=0; r < 16; r++) {
        if (current_player.layer - 1 < r) {
            AnimatePlayer(&current_player);
        }
        for (int e=0; e < 64; e++) {
            if (IsTextureValid(tex_cont[r][e].tex)) {
                if (true) { 
                    DrawTexture(tex_cont[r][e].tex, 
                        tex_cont[r][e].x_pos,
                        tex_cont[r][e].y_pos,
                        WHITE);
                }
                else {

                }
            }
        }
        if (current_player.layer - 1 >= r) {
            AnimatePlayer(&current_player);
        }
    }
}