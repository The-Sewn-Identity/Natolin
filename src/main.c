#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"
#include "levels.h"
#include "player.h"
#include "speech.h"
#include "interface.h"
#include <stdio.h>
#include "util.h"

int main(void) {    
    RaylibInitialize();
    MenuLoad();

    Color default_fill_color = PAXBEIGE;
    bool launched = true;

    current_player = CreatePlayer();
    
    while (!WindowShouldClose()) {
        if (launched) {
            BeginTextureMode(playbox.rendertex);
                ClearBackground(default_fill_color);
                RenderLevel(*current_tex_cont);
                UpdatePlayer(&current_player);
                DrawText(TextFormat("Layer %d", current_player.layer), 10, 0, 10, SLOBODA);
                DrawText(TextFormat("Vector factor XL, XR: %f, %f", current_player.vect_factor.x_left, current_player.vect_factor.x_right), 10, 20, 10, SLOBODA);
                DrawText(TextFormat("Vector factor YD, YU: %f, %f", current_player.vect_factor.y_down, current_player.vect_factor.y_up), 10, 30, 10, SLOBODA);
                DrawText(TextFormat("Player CX, CY: %f,%f", 
                    current_player.rect.x + current_player.rect.width/2, current_player.rect.y + current_player.rect.height/2), 10, 40, 10, SLOBODA);
            EndTextureMode();

            DrawPanel();
            DrawInventory();
            DrawInterface();
        }
        
        BeginDrawing();
            ClearBackground(PAXVIRID);
            if (launched) {
                DrawPlaybox();
                DrawTexturePro(interface.texture,
                    (Rectangle){0, 0, interface.texture.width, -interface.texture.height},
                    (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                    (Vector2){0, 0},
                    0, WHITE
                );
            }
            if (IsKeyDown(KEY_L)) { MenuDraw(); }
        EndDrawing();
    };

    RaylibDeinitialize();
    return 0;
}

// add a draw game function or something
// inline int RenderGame() {    
// }