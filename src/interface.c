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

float interface_ar_factor_w = 0;
float interface_ar_factor_h = 0;

Playbox playbox;

RenderTexture2D panel;
RenderTexture2D inventory;
RenderTexture2D interface;
Texture2D panel_tex;
Texture2D inventory_tex;

void CheckEquipmentButton(void) {

}

IButton ibuttons_arr[] = {
    { .tex_arr = {{0}, {0}}, .vect = {0, 0}, "teq", false, CheckEquipmentButton },
    { .tex_arr = {{0}, {0}}, .vect = {0, 0}, "...", false, CheckEquipmentButton }
};
const unsigned int ibutton_count = ARRAYSIZE(ibuttons_arr);

// move playbox functions somewhere else

void DrawPlaybox(void) {
    DrawTexturePro(playbox.rendertex.texture, 
        (Rectangle){0, 0, playbox.rendertex.texture.width, -playbox.rendertex.texture.height}, 
        (Rectangle){
            (panel_tex.width - RENDERBOXWIDTH - playbox_offset_x) * interface_ar_factor_w, 
            (panel_tex.height - RENDERBOXHEIGHT - playbox_offset_y) * interface_ar_factor_h,
            RENDERBOXWIDTH * interface_ar_factor_w,
            RENDERBOXHEIGHT * interface_ar_factor_h
        }, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void CreatePanel(void) {
    Texture2D panels_arr[ASPECT_RATIO_COUNT];

    panels_arr[ASPECT_RATIO_STANDARD] = LoadTexture("assets/textures/interface/game_STANDARD.png");
    panels_arr[ASPECT_RATIO_WIDESCREEN_16x9] = LoadTexture("assets/textures/interface/game_WIDESCREEN_16x9.png");
    panels_arr[ASPECT_RATIO_WIDESCREEN_16x10] = LoadTexture("assets/textures/interface/game_WIDESCREEN_16x10.png");

    panel_tex = panels_arr[currentAspectRatio];
    panel = LoadRenderTexture(panel_tex.width, panel_tex.height);

    bars_width = panel_tex.width - RENDERBOXWIDTH;
    bars_height = panel_tex.height - RENDERBOXHEIGHT;

    playbox_offset_x = panel_tex.width/2 - RENDERBOXWIDTH/2;
    playbox_offset_y = panel_tex.height/2 - RENDERBOXHEIGHT/2;

    playbox.position.x = bars_width - playbox_offset_x;
    playbox.position.y = -false * playbox_offset_y;

    for (int p=0; p < ibutton_count; p++) {
        ibuttons_arr[p].tex_arr[0] = LoadTexture(TextFormat("assets/textures/interface/%s.png", ibuttons_arr[p].name));
        ibuttons_arr[p].tex_arr[1] = LoadTexture(TextFormat("assets/textures/interface/%s_clicked.png", ibuttons_arr[p].name));
    }
}

void DrawPanel(void) {
    BeginTextureMode(panel);
        ClearBackground(BLANK);
        DrawTexture(panel_tex, 0, 0, WHITE);
        for (int t=0; t < ibutton_count; t++)
        {
            IButton btn = ibuttons_arr[t];

            DrawTextureEx(btn.tex_arr[btn.state], btn.vect, 0, 1.0f, WHITE);
            btn.func();
        }

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
    char * inv_text = "Ekwipunek";

    Rectangle inventory_rect = {
        RENDERBOXWIDTH/2 - inventory_tex.width/2,
        RENDERBOXHEIGHT/12, 
        inventory_tex.width, inventory_tex.height
    };
    
    bool display_text = false;
    Vector2 textlen;
    
    Vector2 mousevect;
    
    Item * items = ((Item*)current_player.items.array);
    int a = 0;
    
    BeginTextureMode(inventory);
        ClearBackground(BLANK);
        DrawTexture(inventory_tex, 0, 0, WHITE);

        mousevect = (Vector2){
            GetMousePosition().x / interface_ar_factor_w,
            GetMousePosition().y / interface_ar_factor_h
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
                    playbox.position.x + inventory_rect.x + slot_x, 
                    playbox.position.y + inventory_rect.y + slot_y, 
                    68, 68
                };
                
                if (CheckCollisionPointRec(mousevect, item_rect)) 
                {
                    inv_text = items[a].name;
                    display_text = true;
                }
                a++;
            }
            if (slot_x == 270 && slot_y == 20) { slot_x = 20 - 83; slot_y += 84; }
        }

        if (display_text)
        { 
            DrawTextbox(inv_text,
                (Vector2){
                    mousevect.x - (playbox_offset_x + inventory_rect.x),
                    mousevect.y - (playbox_offset_y + inventory_rect.y)
                },
                INFO
            );
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
    interface_ar_factor_w = (float) GetScreenWidth() / interface.texture.width;
    interface_ar_factor_h = (float) GetScreenHeight() / interface.texture.height; // width factor is more accurate

    playbox.rendertex = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
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
        
        // teoretycznie, jeśli interfejs można będzie dostosowywać,
        // można użyć boolean jako mnożnika dla offsetów
        if (IsKeyDown(KEY_T)) {
            DrawTexturePro(inventory.texture,
                (Rectangle){0, 0, inventory.texture.width, -inventory.texture.height}, 
                (Rectangle){
                    playbox.position.x + RENDERBOXWIDTH/2 - inventory_tex.width/2,
                    playbox.position.y + RENDERBOXHEIGHT/12, 
                    inventory_tex.width, inventory_tex.height
                },
                (Vector2){0, 0},
                0, WHITE
            );
        }

    EndTextureMode();
}

void UnloadInterface(void) {
    UnloadRenderTexture(playbox.rendertex);

    UnloadRenderTexture(interface);
    UnloadRenderTexture(inventory);
    UnloadRenderTexture(panel);

    UnloadTexture(inventory_tex);
    UnloadTexture(panel_tex);
}