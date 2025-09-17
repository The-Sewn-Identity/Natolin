#include <raylib.h>
#include <stdlib.h>
#include "system_defs.h"
#include "interface.h"
#include "colors.h"
#include "fonts.h"
#include "util.h"

RenderTexture2D playbox;
RenderTexture2D bars;
Texture2D barstex;
Texture2D inventory;
RenderTexture2D rendinvent;

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
    barstex = LoadTexture("assets/textures/interface/game_.png");

    inventory = LoadTexture("assets/textures/interface/inventory_.png");
    rendinvent = LoadRenderTexture(inventory.width, inventory.height);
}

void UnloadInterface(void) {
    UnloadRenderTexture(bars);
    UnloadRenderTexture(rendinvent);
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

void DrawInventory(void) {
    float wfactor = (float)GetScreenWidth() / bars.texture.width;
    Rectangle inventory_rect = {GetScreenWidth()/2 - (rendinvent.texture.width * wfactor)/2,
        GetScreenHeight()/12, rendinvent.texture.width * wfactor, rendinvent.texture.height * wfactor};

    Vector2 textlen = MeasureTextEx(ModernDOS, "Ekwipunek", 16, 3);

    BeginTextureMode(rendinvent);
        DrawTexture(inventory, 0, 0, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), inventory_rect)) {
            DrawText("INSIDE", 20, 20, 56, EINHEIT);
        }
        DrawTextEx(ModernDOS, "Ekwipunek", (Vector2){rendinvent.texture.width/2 - textlen.x/2, rendinvent.texture.height - 23}, 16, 3, CIVICYAN);
    EndTextureMode();
    DrawTexturePro(rendinvent.texture, (Rectangle){0, 0, rendinvent.texture.width, -rendinvent.texture.height}, inventory_rect,
        (Vector2){0, 0},
        0, WHITE);
}