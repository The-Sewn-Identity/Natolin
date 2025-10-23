#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "system_defs.h"
#include "interface.h"
#include "speech.h"
#include "player.h"
#include "colors.h"
#include "fonts.h"
#include "util.h"

#define bar_width 48
#define res_of_inv_item 70

RenderTexture2D playbox;
RenderTexture2D bars;
RenderTexture2D inventory;
Texture2D bars_tex;
Texture2D inventory_tex;

void CreatePlaybox(void) {
    playbox = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
}

void DrawPlaybox(void) {
    DrawTexturePro(playbox.texture, 
        (Rectangle){0, 0, playbox.texture.width, -playbox.texture.height}, 
        (Rectangle){0, 0,
            GetScreenWidth(), GetScreenHeight()}, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void UnloadPlaybox(void) {
    UnloadRenderTexture(playbox);
}

void CreatePanel(void) {
    switch (currentAspectRatio) {
        case ASPECT_RATIO_STANDARD:
            bars_tex = LoadTexture("assets/textures/interface/game_STANDARD.png");
            break;
        case ASPECT_RATIO_WIDESCREEN_16x9:
            bars_tex = LoadTexture("assets/textures/interface/game_WIDESCREEN_16x9.png");
            break;
        case ASPECT_RATIO_WIDESCREEN_16x10:
            break;
        default:
            break;
    }

    bars = LoadRenderTexture(bars_tex.width, bars_tex.height);
}

void UnloadPanel(void) {
    UnloadRenderTexture(bars);
    UnloadTexture(bars_tex);
}

void DrawPanel(void) {
    DrawTexturePro(bars.texture,
        (Rectangle){0, 0, bars.texture.width, -bars.texture.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0},
        0, WHITE
    );
}

void CreateInventory(void) {
    inventory_tex = LoadTexture("assets/textures/interface/inventory_.png");
    inventory = LoadRenderTexture(inventory_tex.width, inventory_tex.height);
}

void DrawInventory(void) {
    float wfactor = (float)GetScreenWidth() / bars.texture.width;
    int slot_x = 20; int slot_y = 20;

    Rectangle inventory_rect = {
        GetScreenWidth()/2 - (inventory.texture.width * wfactor)/2,
        GetScreenHeight()/12, inventory.texture.width * wfactor, 
        inventory.texture.height * wfactor
    };
    
    char * inv_text = "Ekwipunek";
    bool display_text = false;
    Vector2 textlen;
    
    int scr_inv_rat = (float)bars_tex.height / inventory_tex.height;
    Vector2 mousevect;
    
    Item * items = ((Item*)current_player.items.array);
    int a = 0;
    
    BeginTextureMode(inventory);
        ClearBackground(BLANK);
        DrawTexture(inventory_tex, 0, 0, WHITE);

        mousevect = (Vector2){
            inventory_rect.x + GetMousePosition().x / scr_inv_rat,
            inventory_rect.y + GetMousePosition().y / scr_inv_rat
        };
        
        for (; slot_x <= 270; slot_x += ((slot_x == 103) ? 84 : 83)) {
            if (a < current_player.items.size / sizeof(Item))
            {
                DrawTexturePro(items[a].menutex,
                    (Rectangle){0, 0, items[a].menutex.width, items[a].menutex.height },
                    (Rectangle){slot_x, slot_y, 68, 68},
                    (Vector2){0, 0}, 0, WHITE
                );

                Rectangle irect = (Rectangle){
                    inventory_rect.x + slot_x * wfactor, 
                    inventory_rect.y + slot_y * wfactor, 
                    68 * wfactor, 68 * wfactor
                };

                // mouse pos on screen doesn't align with mouse pos in window
                
                if (CheckCollisionPointRec(GetMousePosition(), irect)) 
                {
                    inv_text = items[a].name;
                    DrawTextbox(inv_text, mousevect, INFO);
                }
                a++;
            }
            if (slot_x == 270 && slot_y == 20) { slot_x = 20 - 83; slot_y += 84; }
        }

        textlen = MeasureTextEx(ModernDOS, inv_text, 17, 3);

        DrawTextEx(ModernDOS, inv_text, 
            (Vector2){
                inventory.texture.width/2 - textlen.x/2,
                inventory.texture.height - 23
            }, 17, 3, CIVICYAN
        );

    EndTextureMode();
    
    DrawTexturePro(inventory.texture,
        (Rectangle){0, 0, inventory.texture.width, -inventory.texture.height}, 
        (Rectangle)inventory_rect,
        (Vector2){0, 0},
        0, WHITE
    );
}

void UnloadInventory() {
    UnloadRenderTexture(inventory);
    UnloadTexture(inventory_tex);
}


void CreateInterface(void) {
    CreatePlaybox();
    CreatePanel();
    CreateInventory();
}

void UnloadInterface(void) {
    UnloadPlaybox();
    UnloadPanel();
    UnloadInventory();
}