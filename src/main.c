#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"
#include "levels.h"
#include "render.h"
#include <stdio.h>

int main(void) {
    RaylibInitialize();
    MenuLoad();
    Color default_fill_color = PAXGREEN;
    bool launched = false;

    LSL_Texture_Container lev1;
    CreateLSLTexCont(lev1, level_01);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(default_fill_color);
            if (IsKeyDown(KEY_L)) { MenuDraw(); }
            if (IsKeyPressed(KEY_T) && !launched) {
            }
            RenderLSL(lev1);
        EndDrawing();
    };

    RaylibDeinitialize();
    return 0;
}