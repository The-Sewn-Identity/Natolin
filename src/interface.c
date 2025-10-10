#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "system_defs.h"
#include "interface.h"
#include "player.h"
#include "colors.h"
#include "fonts.h"
#include "util.h"

#define res_of_inv_item 70

RenderTexture2D playbox;
RenderTexture2D bars;
Texture2D barstex;
Texture2D inventory;
RenderTexture2D rendinvent;

unsigned int * aspA;
unsigned int * aspB;

void CreatePlayBox(void) {
    playbox = LoadRenderTexture(RENDERBOXWIDTH, RENDERBOXHEIGHT);
    aspA = malloc(sizeof(unsigned int)); aspB = malloc(sizeof(unsigned int));

    *aspA = 3; *aspB = 2;
}

void DrawPlayBox(void) {
    DrawTexturePro(playbox.texture, 
        (Rectangle){0, 0, playbox.texture.width, -playbox.texture.height}, 
        (Rectangle){GetScreenWidth()/2 - (GetScreenHeight()/(*aspB) * (*aspA))/2, 0,
            GetScreenHeight()/(*aspB) * (*aspA), GetScreenHeight()}, 
        (Vector2){0, 0}, 
        0, WHITE);
}

void UnloadPlayBox(void) {
    UnloadRenderTexture(playbox);
    FREEPTR(aspA); FREEPTR(aspB);
}

void CreateInterface(void) {
    int aspW; int aspH;
    switch (currentAspectRatio) {
        case ASPECT_RATIO_STANDARD:
            break;
        case ASPECT_RATIO_WIDESCREEN_16x9:
            aspW = 16; aspH = 9;
            break;
        case ASPECT_RATIO_WIDESCREEN_16x10:
            break;
        default:
            break;
    }
    bars = LoadRenderTexture(ceil((float)RENDERBOXHEIGHT/aspH) * aspW, RENDERBOXHEIGHT);
    barstex = LoadTexture("assets/textures/interface/game_.png");

    inventory = LoadTexture("assets/textures/interface/inventory_.png");
    rendinvent = LoadRenderTexture(inventory.width, inventory.height);
}

void UnloadInterface(void) {
    UnloadRenderTexture(bars);
    UnloadRenderTexture(rendinvent);
    UnloadTexture(barstex);
    UnloadTexture(inventory);
}

void DrawInterface(void) {
    DrawTexturePro(bars.texture,
        (Rectangle){0, 0, bars.texture.width, -bars.texture.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0},
        0, WHITE
    );
}

void DrawInventory(void) {
    float wfactor = (float)GetScreenWidth() / bars.texture.width;
    int slot_x = 20; int slot_y = 20;

    Rectangle inventory_rect = {
        GetScreenWidth()/2 - (rendinvent.texture.width * wfactor)/2,
        GetScreenHeight()/12, rendinvent.texture.width * wfactor, 
        rendinvent.texture.height * wfactor
    };

    char * inv_text = "Ekwipunek";
    Vector2 textlen;
    
    Item * items = ((Item*)current_player.items.array);
    int a = 0;
    
    BeginTextureMode(rendinvent);
        ClearBackground(BLANK);
        DrawTexture(inventory, 0, 0, WHITE);
        
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
                
                if (CheckCollisionPointRec(GetMousePosition(), irect)) 
                {
                    inv_text = items[a].name;
                }
                a++;
            }
            if (slot_x == 270 && slot_y == 20) { slot_x = 20 - 83; slot_y += 84; }
        }
        textlen = MeasureTextEx(ModernDOS, inv_text, 16, 3);
        DrawTextEx(ModernDOS, inv_text, 
            (Vector2){
                rendinvent.texture.width/2 - textlen.x/2,
                rendinvent.texture.height - 23
            }, 16, 3, CIVICYAN
        );
    EndTextureMode();
    
    DrawTexturePro(rendinvent.texture,
        (Rectangle){0, 0, rendinvent.texture.width, -rendinvent.texture.height}, 
        (Rectangle)inventory_rect,
        (Vector2){0, 0},
        0, WHITE
    );
}