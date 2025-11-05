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
        .x_pos = 240 + 100,
        .y_pos = 160 + 50,
        .speed = 20.0f,
        .offset_x = 0,
        .offset_y = 0,
        .offset_z = 1,
        .param = NULL,
        .ability = Interact
    };
    LoadPlayerAnimations(&pl.animations);
    pl.current_tex = pl.animations[0][0];
    
    pl.items.size = 2 * sizeof(Item); pl.items.array = (Item*)malloc(pl.items.size);
    ((Item*)pl.items.array)[0] = CreateItem(STANDARD, "the egel", "zbowideagle");
    ((Item*)pl.items.array)[1] = CreateItem(STANDARD, "le pax", "paxlogo");

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
                //printf("%d \x", CheckCollisionRecs((*current_tex_cont)[r][e].rect, _player->rect));
            }
        }
    }
}

void GetVectFactor(Player *_player) {
    unsigned int layer = _player->layer - 1;
    float x = 0; float y = 0; float pzpr = 0;

    Trajectory *trajLayer = &(*current_traject)[layer];
    float fpx; float npx;
    float fpy; float npy;

    for (int l=0; l < trajLayer->count - 1; l++) {
        fpx = trajLayer->vect_arr[l].x; npx = trajLayer->vect_arr[l + 1].x;
        fpy = trajLayer->vect_arr[l].y; npy = trajLayer->vect_arr[l + 1].y;

        x = fabsf(fpx - npx); y = fabsf(fpy - npy);
        pzpr = PYTHAGORAS(x, y);
        
        if (WITHIN(fpx, npx, _player->rect.x + _player->rect.width/2) 
            && WITHIN(fpy, npy, _player->rect.y + _player->rect.height/2))
        {
            _player->vect_factor.x_right = (x/pzpr); _player->vect_factor.x_left = -(x/pzpr);
            _player->vect_factor.y_down = sqrt((pzpr/y)); _player->vect_factor.y_up = -sqrt((pzpr/y));

            if (trajLayer->layer >= 1 && trajLayer->layer < 15) {
                for (int a=0; a < (*current_traject)[layer - 1].count - 1; a++) {
                    float pfpx = (*current_traject)[layer - 1].vect_arr[a].x;
                    float pfpy = (*current_traject)[layer - 1].vect_arr[a].y;
                    float pnpx = (*current_traject)[layer - 1].vect_arr[a+1].x;
                    float pnpy = (*current_traject)[layer - 1].vect_arr[a+1].x;

                    if (WITHIN(pfpx, pnpx, _player->rect.x + _player->rect.width/2)
                        && WITHIN(pfpy, pnpy, _player->rect.y + _player->rect.height/2)){
                            _player->block_zi = false;
                    }
                    else { _player->block_zi = true; }
                }
                // for (int b=0; b < (*current_traject)[layer + 1].count - 1; b++) {
                //     float nfpx = (*current_traject)[layer + 1].vect_arr[b].x;
                //     float nfpy = (*current_traject)[layer + 1].vect_arr[b].y;
                //     float nnpx = (*current_traject)[layer + 1].vect_arr[b+1].x;
                //     float nnpy = (*current_traject)[layer + 1].vect_arr[b+1].x;

                //     if (WITHIN(nfpx, nnpx, _player->rect.x + _player->rect.width/2)
                //         && WITHIN(nfpy, nnpy, _player->rect.y + _player->rect.height/2)){
                //             _player->block_zo = false;
                //     }
                //     else { _player->block_zo = true; }
                // }
            }   
        }
        else
        {
            if (rhlval(fpx, npx, '>') < _player->rect.x + _player->rect.width/2) {
                _player->x_pos -= 0.5f;
            }
            if (_player->rect.x + _player->rect.width/2 < rhlval(fpx, npx, '<')) {
                _player->x_pos += 0.5f;
            }
            if (rhlval(fpy, npy, '<') > _player->rect.y + _player->rect.height/2) {
                _player->y_pos += 0.5f;
            }
            if (_player->rect.y + _player->rect.height/2 > rhlval(fpy, npy, '>')) {
                _player->y_pos -= 0.5f;
            }
        }
    }
}

void MovePlayer(Player *_player) {
    _player->layer = 16 - roundf(_player->offset_z) + 1;
    _player->z_speed = _player->current_tex.height/_player->layer;
    GetVectFactor(_player);

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (_player->layer > 1 && !_player->block_zi) { 
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
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //if (_player->layer > 1) { _player->offset_z -= 5 * GetFrameTime(); }
        _player->x_pos += _player->speed * _player->vect_factor.x_right * GetFrameTime();
    }

    //_player->x_pos = GetMouseX();
    //_player->y_pos = GetMouseY();
}

void Inspect(Player *_player) {
}

void Interact(Player *_player) {
    if (IsKeyPressed(KEY_ENTER)) 
    {
        for (int a=0; a < 16; a++) {
            for (int b=0; b < 64; b++){
                TextureDef *texdef = &(*current_tex_cont)[a][b];
                if (CheckCollisionRecs(_player->rect, texdef->rect))
                {
                    if (a == _player->layer - 1 && texdef->feature != NULL) 
                    {
                        if (texdef->feature == Open) {
                            _player->param = (bool*)!(texdef->tex_num);
                        }
                        texdef->feature(texdef, _player->param);
                    }
                }
                else {
                    _player->param = NULL;
                }
            }
        }
    }
    //TraceLog(LOG_INFO, TextFormat("%d,  %d", _player->layer, _player->param));
}