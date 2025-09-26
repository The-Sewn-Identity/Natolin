#include <raylib.h>
#include "system_defs.h"
#include "interface.h"
#include "levels.h"
#include "conf.h"
#include "fonts.h"

void RaylibInitialize(void) {
    LoadLevels();

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), TITLE);
    SetTargetFPS(DEFAULT_FPS);

    SetCurrentAspectRatio();
    CreatePlayBox();
    CreateInterface();

    LoadTextureContainers();
    LoadTrajectories();
    FontsLoad();
}

void RaylibDeinitialize(void) {
    UnloadPlayBox();
    UnloadInterface();
    FontsUnload();
    FreeLSLTextCont(PAX_Container_01);
    CloseWindow();
}