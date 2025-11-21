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
        .center_x = 158,
        .center_y = 245,
        .speed = 20.0f,
        .offset_x = 0,
        .offset_y = 0,
        .offset_z = 1,
        .param = NULL,
        .ability = Interact
    };
    LoadPlayerAnimations(&pl.animations);
    pl.current_tex = pl.animations[0][0];

    pl.x_pos = pl.center_x - pl.current_tex.width/2;
    pl.y_pos = pl.center_y - pl.current_tex.height/2;

    const float VF = cbrtf(pl.speed);
    pl.vect_factor = (struct vect_factor){ -VF, VF, VF, -VF };
    
    pl.items.size = 2 * sizeof(Item); pl.items.array = (Item*)malloc(pl.items.size);
    ((Item*)pl.items.array)[0] = CreateItem(STANDARD, "the egel", "zbowideagle");
    ((Item*)pl.items.array)[1] = CreateItem(STANDARD, "le pax", "paxlogo");

    return pl;
}

void UnloadPlayer(Player *_player) {

}

void UpdatePlayer(Player *_player) {
    MovePlayer(_player);
    CheckIfPlayerInField(_player);
    _player->ability(_player);
}

void AnimatePlayer(Player *_player) {
    _player->scale_vect = (Vector2){
            _player->x_pos + (_player->current_tex.width 
            - PlayerScale(_player) * _player->current_tex.width)/2,
            _player->y_pos + (_player->current_tex.height
            - PlayerScale(_player) * _player->current_tex.height)/2
        },
    DrawTextureEx(
        _player->current_tex,
        _player->scale_vect,
        0, PlayerScale(_player), WHITE
    );
}

void CheckIfPlayerInField(Player *_player) {
    for (int f=0; f < current_fieldset->fieldcount; f++)
    {
        r_array *point_arr = &(current_fieldset->field_arr[f].point_arr);
        int len = point_arr->size / sizeof(Vector2);

        int player_layer = _player->layer - 1;
        int layer_diff = player_layer - current_fieldset->field_arr[f].layer;
        
        Vector2 torso = (Vector2){ _player->center_x + _player->rect.width * 0.75f, _player->center_y + _player->rect.height/3 };
        Vector2 betleg = (Vector2){ _player->center_x, _player->center_y + _player->rect.height / 2.25f };
    
        if (layer_diff == 1)
        {
            if (CheckCollisionPointPoly(torso, point_arr->array, len)) {
                _player->offset_z += layer_diff;
                printf("INSIDE\n");
            }
        }
        else if (layer_diff == -1) {
            if (CheckCollisionPointPoly(betleg, point_arr->array, len)) {
                _player->offset_z += layer_diff;
                printf("INSIDE\n");
            }
        }
        else if (layer_diff == 0)
        {
            Vector2 *fcenter = &current_fieldset->field_arr[f].center;
            float x_axis_diff = betleg.x - fcenter->x;
            float y_axis_diff = betleg.y - fcenter->y;

            if (CheckCollisionPointPoly(betleg, point_arr->array, len)) {
                float VF = cbrtf(_player->speed);

                _player->vect_factor.left = -VF;
                _player->vect_factor.right = VF;
                _player->vect_factor.down = VF;
                _player->vect_factor.up = -VF;
            }
            else {
                if (x_axis_diff <= 0) _player->vect_factor.left = 0;

                if (x_axis_diff > 0) _player->vect_factor.right = 0;

                if (y_axis_diff > 0) _player->vect_factor.down = 0;

                if (y_axis_diff <= 0) _player->vect_factor.up = 0;
            }
        }
    }
}

void MovePlayer(Player *_player) {
    _player->layer = 16 - roundf(_player->offset_z) + 1;
    _player->z_speed = _player->current_tex.height/_player->layer;

    _player->rect = (Rectangle){
        _player->scale_vect.x,
        _player->scale_vect.y,
        _player->current_tex.width * PlayerScale(_player),
        _player->current_tex.height * PlayerScale(_player),
    };
    
    _player->center_x = _player->rect.x + _player->rect.width/2;
    _player->center_y = _player->rect.y + _player->rect.height/2;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        // if (_player->layer > 1) { 
        //     _player->offset_z += _player->z_speed
        //     * GetFrameTime();
        // }
        _player->y_pos += _player->speed * _player->vect_factor.up * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        // if (_player->layer < 16) {
        //     _player->offset_z -= _player->z_speed
        //     * GetFrameTime();
        // }
        _player->y_pos += _player->speed * _player->vect_factor.down * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        _player->x_pos += _player->speed * _player->vect_factor.left * GetFrameTime();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        _player->x_pos += _player->speed * _player->vect_factor.right * GetFrameTime();
    }
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