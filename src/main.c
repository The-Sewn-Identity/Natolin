#include <raylib.h>
#include "menu.h"
#include "conf.h"
#include "colors.h"

int main() {
    RaylibInitialize();
    MenuLoad();
    Color default_fill_color = PAXGREEN;
    bool launched = false;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(default_fill_color);
            if (IsKeyDown(KEY_L)) { MenuDraw(); }
            if (IsKeyPressed(KEY_T) && !launched) {
            }
        EndDrawing();
    };

    RaylibDeinitialize();
    return 0;
}