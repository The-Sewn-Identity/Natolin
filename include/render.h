#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include <lslread.h>
#include "util.h"

enum TextureIndexes {
    DEFAULT = 0,
    OPEN = 1,
};

typedef struct TextureDef {
    r_array tex_arr;
    Rectangle rect;
    unsigned int tex_num;
    int index;
    int x_pos;
    int y_pos;
    void (*feature)(struct TextureDef *);
    char * name;
} TextureDef;

void Open(TextureDef * texdef);
void NextLevel(TextureDef * texdef);
void DefaultFunc(TextureDef * texdef);

typedef TextureDef LSL_Texture_Container[16][64];

void CreateTextureDef(TextureDef * texdef, LSL_Object * object, char *levelname);
void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout);

void RenderLevel(LSL_Texture_Container tex_cont);
void FreeLSLTextCont(LSL_Texture_Container tex_cont);

#endif