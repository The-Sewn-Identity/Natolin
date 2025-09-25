#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "levels.h"
#include "interface.h"
#include "util.h"

#define SHORTDIR "assets/textures/player/%s/%s"

// GET RID OF THE UNDERSCORES SOMEHOW
// THEY'RE BAD

Player current_player;

void LoadPlayerAnimations(Texture2D *** _animations) {
    // 1st array - Idle animations
    // 4th array - Inspect animations
    *_animations = malloc(1 * sizeof(Texture2D*));
    (*_animations)[0] = malloc(sizeof(Texture2D));

    (*_animations)[0][0] = LoadTexture("assets/textures/player/player_.png");
}

float PlayerScale(Player *__player) {
 
    return sinf(atan2(__player->current_tex.height/16, (int)__player->offset_z));
}

Player CreatePlayer(void) {
    Player pl = {
        .fname = "Stanisław",
        .lname = "Konieczny",
        .x_pos = GetRenderCenterX() + 100,
        .y_pos = GetRenderCenterY() + 50,
        .speed = 20.0f,
        .offset_x = 0,
        .offset_y = 0,
        .offset_z = 1,
        .items = {},
        .ability = Interact
    };
    LoadPlayerAnimations(&pl.animations);
    pl.current_tex = pl.animations[0][0];
    
    pl.items[0] = (Item){.item_type = STANDARD, .name = "zbowideagle"}; pl.item_count = 1;

    return pl;
}

void UnloadPlayer(Player *__player) {

}

void UpdatePlayer(Player *__player) {
    PlayerCollision(__player);
    MovePlayer(__player);
    __player->ability(__player);
}

void AnimatePlayer(Player *__player) {
    __player->vect = (Vector2){
            __player->x_pos + (__player->current_tex.width 
            - PlayerScale(__player) * __player->current_tex.width)/2,
            __player->y_pos + (__player->current_tex.height
            - PlayerScale(__player) * __player->current_tex.height)/2
        },
    DrawTextureEx(
        __player->current_tex,
        __player->vect,
        0, PlayerScale(__player), WHITE
    );
}

void PlayerCollision(Player * __player) {
    __player->rect = (Rectangle){
        __player->vect.x,
        __player->vect.y,
        __player->current_tex.width * PlayerScale(__player),
        __player->current_tex.height * PlayerScale(__player),
    };
    for (int r=0; r < 16; r++) {
        for (int e=0; e < 64; e++) {
            if (r == __player->layer - 1) {
                //printf("%d \x1", CheckCollisionRecs((*current_tex_cont)[r][e].rect, __player->rect));
            }
        }
    }
}

void GetVectFactor(Player *__player) {
    unsigned int layer = __player->layer - 1;
    float x1 = 0; float y = 0; float pzpr = 0;

    float fpx; float npx;
    float fpy; float npy;

    for (int l=0; l < (*current_traject)[layer].count - 1; l++) {
        fpx = (*current_traject)[layer].vect_arr[l].x; npx = (*current_traject)[layer].vect_arr[l + 1].x;
        fpy = (*current_traject)[layer].vect_arr[l].y; npy = (*current_traject)[layer].vect_arr[l + 1].y;

        x1 = fabsf(fpx - npx); y = fabsf(fpy - npy);
        pzpr = PYTHAGORAS(x1, y);

        printf("%d, %d\n", rhlval(fpy, npy, '>'), rhlval(fpy, npy, '<'));
        
        if (WITHIN(fpx, npx, __player->rect.x + __player->rect.width/2) 
            && WITHIN(fpy, npy, __player->rect.y + __player->rect.height/2)) {
            __player->vect_factor.x_right = (x1/pzpr); __player->vect_factor.x_left = -(x1/pzpr);
            __player->vect_factor.y_down = (y/x1); __player->vect_factor.y_up = -(y/x1);
        } else {
            if (rhlval(fpx, npx, '>') < __player->rect.x + __player->rect.width/2) {
                __player->x_pos -= sqrtf(__player->rect.x + __player->rect.width/2 - rhlval(fpx, npx, '>'));
            }
            if (__player->rect.x + __player->rect.width/2 < rhlval(fpx, npx, '<')) {
                __player->x_pos += sqrtf(rhlval(fpx, npx, '<') - __player->rect.x + __player->rect.width/2);
            }
            if (rhlval(fpy, npy, '<') > __player->rect.y + __player->rect.height/2) {
                __player->y_pos += sqrtf(rhlval(fpy, npy, '<') - __player->rect.y + __player->rect.height/2);
            }
            if (__player->rect.y + __player->rect.height/2 > rhlval(fpy, npy, '>')) {
                __player->y_pos -= sqrtf(__player->rect.y + __player->rect.height/2 - rhlval(fpy, npy, '>'));
            }
        }
    }
}

void MovePlayer(Player *__player) {
    __player->layer = 16 - roundf(__player->offset_z) + 1;
    __player->z_speed = __player->current_tex.height/__player->layer;
    GetVectFactor(__player);

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (__player->layer > 1) { 
            __player->offset_z += __player->z_speed
            * GetFrameTime();
        }
        __player->y_pos += __player->speed * __player->vect_factor.y_up * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (__player->layer < 16) {
            __player->offset_z -= __player->z_speed
            * GetFrameTime();
        }
        __player->y_pos += __player->speed * __player->vect_factor.y_down * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos += __player->speed * __player->vect_factor.x_left * GetFrameTime();
        __player->y_pos += __player->speed * __player->vect_factor.y_down * GetFrameTime();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos += __player->speed * __player->vect_factor.x_right * GetFrameTime();
        __player->y_pos += __player->speed * __player->vect_factor.y_up * GetFrameTime();
    }

    //__player->x_pos = GetMouseX();
    //__player->y_pos = GetMouseY();
}

void Inspect(Player *__player) {
}

void Interact(Player *__player) {
    if (IsKeyPressed(KEY_ENTER)) {
        for (int a=0; a < 16; a++) {
            for (int b=0; b < 64; b++) {
                if (CheckCollisionRecs(__player->rect, (*current_tex_cont)[a][b].rect)) {
                    if (a == __player->layer - 1 && (*current_tex_cont)[a][b].feature == Open) {
                        (*current_tex_cont)[a][b].tex;
                    }
                }
            }
        }
    }
}