#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include <lslread.h>


typedef struct TextureDef {
    short int index;
    Texture2D tex;
    Rectangle rect;
    short int x_pos;
    short int y_pos;
    void (*feature)(struct TextureDef *);
    char name[];
} TextureDef;

void Open(TextureDef * texdef);

typedef TextureDef LSL_Texture_Container[16][64];

void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout);

void RenderPlayerAndLSL(LSL_Texture_Container tex_cont);
void FreeLSLTextCont(LSL_Texture_Container tex_cont);

#endif