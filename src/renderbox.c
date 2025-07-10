#include <raylib.h>
#include <stdlib.h>
#include "renderbox.h"
#include "util.h"

RenderTexture2D renderbox;
unsigned short * aspA;
unsigned short * aspB;

void CreateMainRenderBox() {
    renderbox = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
    SetTextureFilter(renderbox.texture, TEXTURE_FILTER_POINT);
    aspA = malloc(sizeof(unsigned short));
    aspB = malloc(sizeof(unsigned short));

    *aspA = 3;
    *aspB = 2;
}

void DrawMainRenderBox() {
    DrawTexturePro(renderbox.texture, 
        (Rectangle){0, 0, renderbox.texture.width, -renderbox.texture.height}, 
        (Rectangle){GetScreenWidth()/2 - (GetScreenHeight()/(*aspB) * (*aspA))/2 , 0, GetScreenHeight()/(*aspB) * (*aspA), GetScreenHeight()}, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void UnloadMainRenderBox() {
    UnloadRenderTexture(renderbox);
    FREEPTR(aspA);
    FREEPTR(aspB);
}

int GetRenderCenterX() {
    return renderbox.texture.width/2;
}

int GetRenderCenterY() {
    return renderbox.texture.height/2;
}