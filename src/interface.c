#include <raylib.h>
#include <stdlib.h>
#include "interface.h"
#include "util.h"

RenderTexture2D playbox;
RenderTexture2D bars;
Texture2D barstex;
Texture2D inventory;

unsigned short * aspA;
unsigned short * aspB;

void CreatePlayBox(void) {
    playbox = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
    //SetTextureFilter(playbox.texture, TEXTURE_FILTER_POINT);
    aspA = malloc(sizeof(unsigned short));
    aspB = malloc(sizeof(unsigned short));

    *aspA = 3;
    *aspB = 2;
}

void DrawPlayBox(void) {
    DrawTexturePro(playbox.texture, 
        (Rectangle){0, 0, playbox.texture.width, -playbox.texture.height}, 
        (Rectangle){GetScreenWidth()/2 - (GetScreenHeight()/(*aspB) * (*aspA))/2 , 0, GetScreenHeight()/(*aspB) * (*aspA), GetScreenHeight()}, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void UnloadPlayBox(void) {
    UnloadRenderTexture(playbox);
    FREEPTR(aspA);
    FREEPTR(aspB);
}

int GetRenderCenterX(void) {
    return playbox.texture.width/2;
}

int GetRenderCenterY(void) {
    return playbox.texture.height/2;
}

// bars
#include <stdio.h>
#include <math.h>

void CreateInterface(void) {
    bars = LoadRenderTexture(ceil((float)RENDERBOXHEIGHT/9) * 16, RENDERBOXHEIGHT);
    printf("%d \n", bars.texture.width);
    barstex = LoadTexture("assets/textures/interface/game_.png");
    inventory = LoadTexture("assets/textures/interface/inventory_.png");
}

void UnloadInterface(void) {
    UnloadRenderTexture(bars);
    UnloadTexture(barstex);
    UnloadTexture(inventory);
}

void DrawInterface(void) {
    DrawTexturePro(bars.texture,
        (Rectangle){0, 0, bars.texture.width, -bars.texture.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0},
        0, WHITE);
}