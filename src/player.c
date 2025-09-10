#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "levels.h"
#include "interface.h"
#include "util.h"

#define SHORTDIR "assets/textures/player/%s/%s"

struct VectFactor { float x; float y; };

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
    return sinf(atan2(__player->current_tex.height/16, __player->layer));
}

Player CreatePlayer(void) {
    Player pl = {
        .fname = "Stanisław",
        .lname = "Konieczny",
        .x_pos = GetRenderCenterX(),
        .y_pos = GetRenderCenterY(),
        .speed = 20.0f,
        .layer = 14,
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
    AnimatePlayer(__player);
    PlayerCollision(__player);
    MovePlayer(__player);
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
                //printf("%d", CheckCollisionRecs(current_tex_cont[r][e]->rect, __player->rect));
            }
        }
    }
}

float GetVectFactor(Player *__player) {
    float n;

    for (int l=0; l < (*current_traject)[__player->layer - 1].count - 1; l++) {
        if (
            (*current_traject)[__player->layer - 1].vect_arr[l].x <= (__player->rect.x + __player->rect.width) - __player->rect.width/2
            && (__player->rect.x + __player->rect.width) - __player->rect.width/2 <= (*current_traject)[__player->layer - 1].vect_arr[l + 1].x
        ) {
            n = PYTHAGORAS(
                fabs((*current_traject)[__player->layer - 1].vect_arr[l].x - (*current_traject)[__player->layer - 1].vect_arr[l + 1].x),
                fabs((*current_traject)[__player->layer - 1].vect_arr[l].y - (*current_traject)[__player->layer - 1].vect_arr[l + 1].y)
            );
        }
    }
    return (float)n/1000;
}

void MovePlayer(Player *__player) {
    __player->layer = roundf(__player->offset_z);
    __player->z_speed = __player->current_tex.height/__player->layer;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (__player->layer < 16) { 
            __player->offset_z += __player->z_speed
            * GetVectFactor(__player)
            * GetFrameTime();
        }
        __player->y_pos -= __player->speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (__player->layer > 1) {
            __player->offset_z -= __player->z_speed
            * GetVectFactor(__player)
            * GetFrameTime();
        }
        __player->y_pos += __player->speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos -= __player->speed * GetVectFactor(__player) * GetFrameTime();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //if (__player->layer > 1) { __player->offset_z -= 5 * GetFrameTime(); }
        __player->x_pos += __player->speed * GetVectFactor(__player) * GetFrameTime();
    }
}

void Inspect(Player *__player) {
}