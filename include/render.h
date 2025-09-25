#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include <lslread.h>

enum TextureIndexes {
    DEFAULT,
    OPEN
};

typedef struct TextureDef {
    union {
        Texture2D tex;
        Texture2D * tex_arr;
    };
    Rectangle rect;
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

void CreateLSLTexCont(LSL_Texture_Container tex_cont, LSL_Layout layout);

void RenderLevel(LSL_Texture_Container tex_cont);
void FreeLSLTextCont(LSL_Texture_Container tex_cont);

#endif