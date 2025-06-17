#include <raylib.h>
#include "conf.h"
#include "fonts.h"

void RaylibInitialize() {
    SetConfigFlags(FLAG_MSAA_4X_HINT || FLAG_FULLSCREEN_MODE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(DEFAULT_FPS);

    FontsLoad();
}

void RaylibDeinitialize() {
    FontsUnload();
    CloseWindow();
}