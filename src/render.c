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
    texdef->tex_num = OPEN;
}

void NextLevel(TextureDef * texdef) {
}

void DefaultFunc(TextureDef * texdef) {
}

Texture2D * TexArrayVect(r_array tex_array) {
    return ((Texture2D*)tex_array.array);
}

void CreateTextureDef(TextureDef * texdef, LSL_Object * object, char *levelname) {
    texdef->tex_num = DEFAULT;
    texdef->index = object->index; texdef->name = object->image;
    texdef->x_pos = object->x_pos; texdef->y_pos = object->y_pos;

    texdef->tex_arr.size = sizeof(Texture2D);
    texdef->tex_arr.array = malloc(texdef->tex_arr.size);
    ((Texture2D*)texdef->tex_arr.array)[DEFAULT] = LoadTexture(TextFormat("assets/textures/levels/%s/%s.png",
            levelname, texdef->name));
    
    if (string_eq(object->feature, "NONE")) {
        texdef->feature = DefaultFunc;
    }
    else if (string_eq(object->feature, "OPEN")) {
        texdef->feature = Open;

        texdef->tex_arr.size = 2 * sizeof(Texture2D);
        texdef->tex_arr.array = nalloc(texdef->tex_arr.array, texdef->tex_arr.size);
        ((Texture2D*)texdef->tex_arr.array)[OPEN] = LoadTexture(TextFormat("assets/textures/levels/%s/%s_open.png",
                levelname, texdef->name));
    }
    else if (string_eq(object->feature, "NEXT__LVL")) {
        texdef->feature = NextLevel;
    }
    else {
        texdef->feature = NULL;
    }
    texdef->rect = (Rectangle){
        texdef->x_pos, texdef->y_pos,
        ((Texture2D*)texdef->tex_arr.array)[DEFAULT].width,
        ((Texture2D*)texdef->tex_arr.array)[DEFAULT].height
    };
}

void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout) {
    for (int o=0; o < 16; o++) {
        for (int r=0; r < 64; r++) {
            CreateTextureDef(&tex_cont[o][r], &layout.layers[o][r], layout.levelname);
        }
    }
}

void FreeLSLTextCont(LSL_Texture_Container tex_cont) {
    Texture2D * tex_arr;
    for (int f=0; f < 16; f++) {
        for (int r=0; r < 64; r++) {
            tex_arr = TexArrayVect(tex_cont[f][r].tex_arr);

            for (int l=0; l < tex_cont[f][r].tex_arr.size / sizeof(Texture2D); l++) {
                UnloadTexture(tex_arr[l]);
            }
        }
    }
}

void RenderLevel(LSL_Texture_Container tex_cont) {
    Texture2D * tex_arr;

    for (int r=0; r < 16; r++) {
        if (current_player.layer - 1 < r) {
            AnimatePlayer(&current_player);
        }
        for (int e=0; e < 64; e++) {
            tex_arr = TexArrayVect(tex_cont[r][e].tex_arr);

            if (IsTextureValid(tex_arr[tex_cont[r][e].tex_num]) ) {
                DrawTexture(tex_arr[tex_cont[r][e].tex_num], 
                    tex_cont[r][e].x_pos,
                    tex_cont[r][e].y_pos,
                    WHITE);
            }
        }
        if (current_player.layer - 1 >= r) {
            AnimatePlayer(&current_player);
        }
    }
}