#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"

typedef struct Player {
    Item items[16];
    Texture2D ** animations;
    Texture2D current_tex;
    Rectangle rect;
    struct { float x_left; float x_right; float y_down; float y_up; } vect_factor;
    Vector2 vect;
    float x_pos; float y_pos;
    float speed; float z_speed; 
    float offset_x;
    float offset_y;
    float offset_z;
    unsigned int layer;
    unsigned int item_count;
    char * fname; char * lname;
    void (*ability)(struct Player *);
} Player;
extern Player current_player;

Player CreatePlayer(void);
void UnloadPlayer(Player *__player);
void UpdatePlayer(Player *_player);

void AnimatePlayer(Player *__player);
void MovePlayer(Player *__player);
void PlayerCollision(Player *__player);
void Inspect(Player *__player);
void Interact(Player *__player);

#endif