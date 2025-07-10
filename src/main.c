#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"
#include "levels.h"
#include "player.h"
#include "interface.h"
#include <stdio.h>

int main(void) {
    RaylibInitialize();
    MenuLoad();

    Color default_fill_color = DEPALERED;
    bool launched = true;

    current_player = CreatePlayer();
    
    while (!WindowShouldClose()) {
        if (launched) {
            BeginTextureMode(playbox);
                ClearBackground(default_fill_color);
                if (IsKeyPressed(KEY_T) && !launched) {
                }
                RenderLSL(*current_tex_cont);
            EndTextureMode();

            BeginTextureMode(bars);
                ClearBackground(BLANK);
                DrawTexture(barstex, 0, 0, WHITE);
            EndTextureMode();
        }
            
        BeginDrawing();
            ClearBackground(PAXGREEN);
            if (launched) {
                DrawPlayBox();
                DrawInterface();
            }
            if (IsKeyDown(KEY_L)) { MenuDraw(); }
        EndDrawing();
    };

    RaylibDeinitialize();
    return 0;
}