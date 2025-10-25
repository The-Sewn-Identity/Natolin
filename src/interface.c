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

#define res_of_inv_item 70

int bars_width = 0, bars_height = 0;
int playbox_offset_x = 0, playbox_offset_y = 0;

int interface_ar_factor = 0;

RenderTexture2D playbox;

RenderTexture2D panel;
RenderTexture2D inventory;
RenderTexture2D interface;
Texture2D panel_tex;
Texture2D inventory_tex;

// move playbox functions somewhere else

void DrawPlaybox(void) {
    DrawTexturePro(playbox.texture, 
        (Rectangle){0, 0, playbox.texture.width, -playbox.texture.height}, 
        (Rectangle){playbox_offset_x * interface_ar_factor, 0, 
            RENDERBOXWIDTH * interface_ar_factor + bars_width * interface_ar_factor, GetScreenHeight()}, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void CreatePanel(void) {
    Texture2D panels_arr[ASPECT_RATIO_COUNT];

    panels_arr[ASPECT_RATIO_STANDARD] = LoadTexture("assets/textures/interface/game_STANDARD.png");
    panels_arr[ASPECT_RATIO_WIDESCREEN_16x9] = LoadTexture("assets/textures/interface/game_WIDESCREEN_16x9.png");
    panels_arr[ASPECT_RATIO_WIDESCREEN_16x10] = LoadTexture("assets/textures/interface/game_WIDESCREEN_16x10.png");

    switch (currentAspectRatio) {
        case ASPECT_RATIO_STANDARD:
            bars_height = 48;
            break;
        case ASPECT_RATIO_WIDESCREEN_16x9:
            playbox_offset_x = 48;
            bars_width = playbox_offset_x * 2;
            break;
        case ASPECT_RATIO_WIDESCREEN_16x10:
            bars_width = 32;
            break;
    }

    panel_tex = panels_arr[currentAspectRatio];

    panel = LoadRenderTexture(panel_tex.width, panel_tex.height);
}

void DrawPanel(void) {
    BeginTextureMode(panel);
        ClearBackground(BLANK);
        DrawTexture(panel_tex, 0, 0, WHITE);
    EndTextureMode();
}

void CreateInventory(void) {
    inventory_tex = LoadTexture("assets/textures/interface/inventory_.png");
    inventory = LoadRenderTexture(inventory_tex.width, inventory_tex.height);
}

// MAKE THE INTERFACE BE ONE RENDERTEXTURE
// why didn't i do this before idk

void DrawInventory(void) {
    int slot_x = 20, slot_y = 20;

    Rectangle inventory_rect = {
        RENDERBOXWIDTH/2 - inventory_tex.width/2,
        RENDERBOXHEIGHT/12, 
        inventory_tex.width, inventory_tex.height
    };
    
    char * inv_text = "Ekwipunek";
    bool display_text = false;
    Vector2 textlen;
    
    int scr_inv_rat = (float) GetScreenHeight() / interface.texture.height;
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
                    (Rectangle){0, 0, items[a].menutex.width, items[a].menutex.height},
                    (Rectangle){slot_x, slot_y, 68, 68},
                    (Vector2){0, 0}, 0, WHITE
                );

                Rectangle item_rect = (Rectangle){
                    playbox_offset_x + (RENDERBOXWIDTH - inventory_rect.width)/2 + inventory_rect.x + slot_x, 
                    playbox_offset_y + inventory_rect.y + slot_y, 
                    68, 68
                };
                
                if (CheckCollisionPointRec(mousevect, item_rect)) 
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
}

void CreateInterface(void) {
    CreatePanel();
    CreateInventory();
    interface = LoadRenderTexture(RENDERBOXWIDTH + bars_width, RENDERBOXHEIGHT + bars_height);
    interface_ar_factor = (float) GetScreenHeight() / interface.texture.height;

    playbox = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
}

void DrawInterface(void) {
    BeginTextureMode(interface);
        ClearBackground(BLANK);

        DrawTexturePro(panel.texture,
            (Rectangle){0, 0, panel.texture.width, -panel.texture.height},
            (Rectangle){0, 0, interface.texture.width, interface.texture.height},
            (Vector2){0, 0},
            0, WHITE
        );
        
        if (IsKeyDown(KEY_T)) {
            DrawTexturePro(inventory.texture,
                (Rectangle){0, 0, inventory.texture.width, -inventory.texture.height}, 
                (Rectangle){
                    playbox_offset_x + RENDERBOXWIDTH/2 - inventory_tex.width/2,
                    playbox_offset_y + RENDERBOXHEIGHT/12, 
                    inventory_tex.width, inventory_tex.height
                },
                (Vector2){0, 0},
                0, WHITE
            );
        }

    EndTextureMode();
}

void UnloadInterface(void) {
    UnloadRenderTexture(playbox);

    UnloadRenderTexture(interface);
    UnloadRenderTexture(inventory);
    UnloadRenderTexture(panel);

    UnloadTexture(inventory_tex);
    UnloadTexture(panel_tex);
}