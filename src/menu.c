#include <string.h>
#include <raylib.h>
#include "renderbox.h"
#include "util.h"
#include "conf.h"
#include "fonts.h"

#define SUBTITLE "Kto nie z Mieciem, tego zmieciem!"

Texture2D logo;
Vector2 textlen;

void MenuLoad(void) {
    logo = LoadTexture("assets/textures/logos/Natolin_logo.png");
    textlen =  MeasureTextEx(Zaklad, SUBTITLE, GetScreenHeight()/15, 1);
}

void MenuUnload(void) {
    UnloadTexture(logo);
}

void MenuDraw(void) {
    DrawTexturePro(logo, 
        (Rectangle){0, 0, logo.width, logo.height},
        (Rectangle){GetScreenWidth() / 2 - logo.width / 2, 0, logo.width, logo.height},
        (Vector2){0, 0},
        0, WHITE
    );
    DrawTextEx(Zaklad, SUBTITLE,
        (Vector2){GetScreenWidth() / 2 - textlen.x/2, GetScreenHeight() / 3}, GetScreenHeight()/15, 1, WHITE);
}