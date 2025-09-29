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

void LoadPlayerAnimations(Texture2D *** _animations) {
    // 1st array - Idle animations
    // 4th array - Inspect animations
    *_animations = malloc(1 * sizeof(Texture2D*));
    (*_animations)[0] = malloc(sizeof(Texture2D));

    (*_animations)[0][0] = LoadTexture("assets/textures/player/player_.png");
}

float PlayerScale(Player *_player) {
 
    return sinf(atan2(_player->current_tex.height/16, (int)_player->offset_z));
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

void UnloadPlayer(Player *_player) {

}

void UpdatePlayer(Player *_player) {
    PlayerCollision(_player);
    MovePlayer(_player);
    _player->ability(_player);
}

void AnimatePlayer(Player *_player) {
    _player->vect = (Vector2){
            _player->x_pos + (_player->current_tex.width 
            - PlayerScale(_player) * _player->current_tex.width)/2,
            _player->y_pos + (_player->current_tex.height
            - PlayerScale(_player) * _player->current_tex.height)/2
        },
    DrawTextureEx(
        _player->current_tex,
        _player->vect,
        0, PlayerScale(_player), WHITE
    );
}

void PlayerCollision(Player * _player) {
    _player->rect = (Rectangle){
        _player->vect.x,
        _player->vect.y,
        _player->current_tex.width * PlayerScale(_player),
        _player->current_tex.height * PlayerScale(_player),
    };
    for (int r=0; r < 16; r++) {
        for (int e=0; e < 64; e++) {
            if (r == _player->layer - 1) {
                //printf("%d \x1", CheckCollisionRecs((*current_tex_cont)[r][e].rect, _player->rect));
            }
        }
    }
}

void GetVectFactor(Player *_player) {
    unsigned int layer = _player->layer - 1;
    float x1 = 0; float y = 0; float pzpr = 0;

    float fpx; float npx;
    float fpy; float npy;

    for (int l=0; l < (*current_traject)[layer].count - 1; l++) {
        fpx = (*current_traject)[layer].vect_arr[l].x; npx = (*current_traject)[layer].vect_arr[l + 1].x;
        fpy = (*current_traject)[layer].vect_arr[l].y; npy = (*current_traject)[layer].vect_arr[l + 1].y;

        x1 = fabsf(fpx - npx); y = fabsf(fpy - npy);
        pzpr = PYTHAGORAS(x1, y);
        
        if (WITHIN(fpx, npx, _player->rect.x + _player->rect.width/2) 
            && WITHIN(fpy, npy, _player->rect.y + _player->rect.height/2)) {
            _player->vect_factor.x_right = (x1/pzpr); _player->vect_factor.x_left = -(x1/pzpr);
            _player->vect_factor.y_down = (y/x1); _player->vect_factor.y_up = -(y/x1);
        } else {
            if (rhlval(fpx, npx, '>') < _player->rect.x + _player->rect.width/2) {
                _player->x_pos -= sqrtf(_player->rect.x + _player->rect.width/2 - rhlval(fpx, npx, '>'));
            }
            if (_player->rect.x + _player->rect.width/2 < rhlval(fpx, npx, '<')) {
                _player->x_pos += sqrtf(rhlval(fpx, npx, '<') - _player->rect.x + _player->rect.width/2);
            }
            if (rhlval(fpy, npy, '<') > _player->rect.y + _player->rect.height/2) {
                _player->y_pos += sqrtf(rhlval(fpy, npy, '<') - _player->rect.y + _player->rect.height/2);
            }
            if (_player->rect.y + _player->rect.height/2 > rhlval(fpy, npy, '>')) {
                _player->y_pos -= sqrtf(_player->rect.y + _player->rect.height/2 - rhlval(fpy, npy, '>'));
            }
        }
    }
}

void MovePlayer(Player *_player) {
    _player->layer = 16 - roundf(_player->offset_z) + 1;
    _player->z_speed = _player->current_tex.height/_player->layer;
    GetVectFactor(_player);

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (_player->layer > 1) { 
            _player->offset_z += _player->z_speed
            * GetFrameTime();
        }
        _player->y_pos += _player->speed * _player->vect_factor.y_up * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (_player->layer < 16) {
            _player->offset_z -= _player->z_speed
            * GetFrameTime();
        }
        _player->y_pos += _player->speed * _player->vect_factor.y_down * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        //if (_player->layer > 1) { _player->offset_z -= 5 * GetFrameTime(); }
        _player->x_pos += _player->speed * _player->vect_factor.x_left * GetFrameTime();
        _player->y_pos += _player->speed * _player->vect_factor.y_down * GetFrameTime();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //if (_player->layer > 1) { _player->offset_z -= 5 * GetFrameTime(); }
        _player->x_pos += _player->speed * _player->vect_factor.x_right * GetFrameTime();
        _player->y_pos += _player->speed * _player->vect_factor.y_up * GetFrameTime();
    }

    //_player->x_pos = GetMouseX();
    //_player->y_pos = GetMouseY();
}

void Inspect(Player *_player) {
}

void Interact(Player *_player) {
    if (IsKeyPressed(KEY_ENTER)) {
        for (int a=0; a < 16; a++) {
            for (int b=0; b < 64; b++) {
                if (CheckCollisionRecs(_player->rect, (*current_tex_cont)[a][b].rect)) {
                    if (a == _player->layer - 1 && (*current_tex_cont)[a][b].feature == Open) {
                        (*current_tex_cont)[a][b].feature(&(*current_tex_cont)[a][b]);
                    }
                }
            }
        }
    }
}