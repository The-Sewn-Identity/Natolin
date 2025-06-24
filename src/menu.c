#include <string.h>
#include <raylib.h>
#include "conf.h"
#include "fonts.h"

#define SUBTITLE "Kto nie z Mieciem, tego zmieciem!"

Texture2D logo;
Vector2 textlen;

void MenuLoad() {
    logo = LoadTexture("assets/textures/logos/Natolin_logo.png");
    textlen =  MeasureTextEx(Zaklad, SUBTITLE, 48, 1);
}

void MenuUnload() {
    UnloadTexture(logo);
}

void MenuDraw() {
    DrawTexture(logo, SCREEN_WIDTH / 2 - logo.width / 2, 0, WHITE);
    DrawTextEx(Zaklad, SUBTITLE,
        (Vector2){SCREEN_WIDTH / 2 - textlen.x/2, SCREEN_HEIGHT / 3}, 48, 1, WHITE);
}