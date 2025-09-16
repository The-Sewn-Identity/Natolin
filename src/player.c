#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "levels.h"
#include "interface.h"
#include "util.h"

#define SHORTDIR "assets/textures/player/%s/%s"

Player current_player;
float z_speed;

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
        .x_pos = GetRenderCenterX() + 140,
        .y_pos = GetRenderCenterY() + 30,
        .speed = 20.0f,
        .offset_x = 0,
        .offset_y = 0,
        .offset_z = 1,
        .ability = Inspect
    };
    LoadPlayerAnimations(&pl.animations);
    pl.current_tex = pl.animations[0][0];

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
    unsigned short layer = __player->layer - 1;
    float x1; float pzpr;
    float y;

    unsigned short lvx = (*current_traject)[layer].vect_arr[0].y; unsigned short svx = lvx;
    unsigned short lvy = (*current_traject)[layer].vect_arr[0].y; unsigned short svy = lvy;
    for (int m=0; m < (*current_traject)[layer].count; m++) { 
        if (lvx < (*current_traject)[layer].vect_arr[m].x) { lvx = (*current_traject)[layer].vect_arr[m].x; }
    }
    for (int m=0; m < (*current_traject)[layer].count; m++) { 
        if (svx > (*current_traject)[layer].vect_arr[m].x) { svx = (*current_traject)[layer].vect_arr[m].x; }
    }
    for (int m=0; m < (*current_traject)[layer].count; m++) { 
        if (lvy < (*current_traject)[layer].vect_arr[m].y) { lvy = (*current_traject)[layer].vect_arr[m].y; }
    }
    for (int m=0; m < (*current_traject)[layer].count; m++) { 
        if (svy > (*current_traject)[layer].vect_arr[m].y) { svy = (*current_traject)[layer].vect_arr[m].y; }
    }

    //printf("[[ %d %d ]]", lvy, svy);

    for (int l=0; l < (*current_traject)[layer].count - 1; l++) {
        if (
            LOCCMP((*current_traject)[layer].vect_arr[l].x, (*current_traject)[layer].vect_arr[l+1].x, __player->rect.x + __player->rect.width/2)
            && LOCCMP((*current_traject)[layer].vect_arr[l].y, (*current_traject)[layer].vect_arr[l+1].y, __player->rect.y + __player->rect.height/2)
        ) {
            x1 = fabsf((*current_traject)[layer].vect_arr[l].x - (*current_traject)[layer].vect_arr[l + 1].x);
            pzpr = PYTHAGORAS(
                (*current_traject)[layer].vect_arr[l].x - (*current_traject)[layer].vect_arr[l + 1].x, 
                (*current_traject)[layer].vect_arr[l].y - (*current_traject)[layer].vect_arr[l + 1].y
            );
            __player->vect_factor.xr = (x1/pzpr); __player->vect_factor.xl = -(x1/pzpr);
            y = fabsf((*current_traject)[layer].vect_arr[l].y - (*current_traject)[layer].vect_arr[l + 1].y);
            __player->vect_factor.yd = (y/x1), __player->vect_factor.yu = -(y/x1);
            break;
        } else {
            if (__player->rect.x + __player->rect.width/2 < (*current_traject)[layer].vect_arr[l].x) { 
                __player->vect_factor.xl = 0; __player->vect_factor.yd = 0; __player->vect_factor.yu = 0;
            }
            if (__player->rect.x + __player->rect.width/2 > (*current_traject)[layer].vect_arr[l + 1].x){
                __player->vect_factor.xr = 0; __player->vect_factor.yd = 0; __player->vect_factor.yu = 0;
            }
            continue;
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
        __player->y_pos += __player->speed * __player->vect_factor.yu * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (__player->layer < 16) {
            __player->offset_z -= __player->z_speed
            * GetFrameTime();
        }
        __player->y_pos += __player->speed * __player->vect_factor.yd * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos += __player->speed * __player->vect_factor.xl * GetFrameTime();
        __player->y_pos += __player->speed * __player->vect_factor.yd * GetFrameTime();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos += __player->speed * __player->vect_factor.xr * GetFrameTime();
        __player->y_pos += __player->speed * __player->vect_factor.yu * GetFrameTime();
    }

    __player->x_pos = GetMouseX();
    __player->y_pos = GetMouseY();
}

void Inspect(Player *__player) {
}