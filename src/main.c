#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"
#include "levels.h"
#include "player.h"
#include "renderbox.h"
#include <stdio.h>

int main(void) {
    RaylibInitialize();
    MenuLoad();

    Color default_fill_color = ZSL_LIME;
    bool launched = true;

    current_player = CreatePlayer();
    
    while (!WindowShouldClose()) {
        if (launched) {
            BeginTextureMode(renderbox);
                ClearBackground(default_fill_color);
                if (IsKeyPressed(KEY_T) && !launched) {
                }
                RenderLSL(*current_tex_cont);
            EndTextureMode();
        }
            
        BeginDrawing();
            ClearBackground(PAXGREEN);
            if (launched) {
                DrawMainRenderBox();
            }
            if (IsKeyDown(KEY_L)) { MenuDraw(); }
        EndDrawing();
    };

    RaylibDeinitialize();
    return 0;
}