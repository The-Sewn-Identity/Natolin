#include <raylib.h>
#include "levels.h"
#include "conf.h"
#include "fonts.h"

void RaylibInitialize(void) {
    LoadLevels();

    SetConfigFlags(FLAG_MSAA_4X_HINT || FLAG_FULLSCREEN_MODE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(DEFAULT_FPS);

    FontsLoad();
}

void RaylibDeinitialize(void) {
    FontsUnload();
    CloseWindow();
}