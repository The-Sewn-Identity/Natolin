#include <raylib.h>
#include "renderbox.h"
#include "levels.h"
#include "conf.h"
#include "fonts.h"

void RaylibInitialize(void) {
    LoadLevels();

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), TITLE);
    SetTargetFPS(DEFAULT_FPS);

    CreateMainRenderBox();

    LoadTextureContainers();
    FontsLoad();
}

void RaylibDeinitialize(void) {
    UnloadMainRenderBox();
    FontsUnload();
    CloseWindow();
}