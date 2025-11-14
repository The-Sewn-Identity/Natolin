#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <extutil.h>
#include "items.h"

typedef struct Player {
    r_array items;
    Texture2D **animations;
    Texture2D current_tex;
    Rectangle rect;
    //  ------
    struct vect_factor { float left;  float right; float down;     float up; } vect_factor;
    struct             { float x_pos; float y_pos; float center_x; float center_y; };
    Vector2 scale_vect;
    float speed; float z_speed;
    //  ------
    float offset_x;
    float offset_y;
    float offset_z;
    //  ------
    char *fname; char *lname;
    void *param;
    void (*ability)(struct Player *);
    //  ------
    uint8_t layer;
} Player;
extern Player current_player;

Player CreatePlayer(void);
void UnloadPlayer(Player *__player);
void UpdatePlayer(Player *_player);

void AnimatePlayer(Player *__player);
void MovePlayer(Player *__player);
void CheckIfPlayerInField(Player *_player);
void Inspect(Player *__player);
void Interact(Player *__player);

#endif