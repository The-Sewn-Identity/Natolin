#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"
#include "levels.h"
#include "player.h"
#include "interface.h"
#include <stdio.h>
#include "util.h"

int main(void) {
    for (int f=16; f > 0; f--) {
        printf("Pos: %f\n", ((float)144/f));
    }
    RaylibInitialize();
    MenuLoad();

    Color default_fill_color = PAXBEIGE;
    bool launched = true;

    current_player = CreatePlayer();
    
    while (!WindowShouldClose()) {
        if (launched) {
            BeginTextureMode(playbox);
                ClearBackground(default_fill_color);
                if (IsKeyPressed(KEY_T) && !launched) {
                }
                RenderLSL(*current_tex_cont);
                UpdatePlayer(&current_player);
                DrawText(TextFormat("Layer %d", current_player.layer), 10, 0, 10, SLOBODA);
                DrawText(TextFormat("Vector factor X: %f", current_player.vect_factor.x), 10, 20, 10, SLOBODA);
            EndTextureMode();

            BeginTextureMode(bars);
                ClearBackground(BLANK);
                DrawTexture(barstex, 0, 0, WHITE);
                if (IsKeyDown(KEY_T)) {
                    DrawTexture(inventory, bars.texture.width/2 - inventory.width/2, bars.texture.height/12, WHITE);
                }
            EndTextureMode();
        }
            
        BeginDrawing();
            ClearBackground(PAXVIRID);
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