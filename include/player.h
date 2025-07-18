#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    Texture2D ** animations;
    Texture2D current_tex;
    char * fname;
    char * lname;
    float x_pos;
    float y_pos;
    float speed; 
    unsigned short layer;
    float offset_x;
    float offset_y;
    float offset_z;
    void (*ability)(struct Player *);
} Player;
extern Player current_player;

Player CreatePlayer(void);
void UnloadPlayer(Player *__player);

void AnimatePlayer(Player *__player);
void MovePlayer(Player *__player);
void Inspect(Player *__player);

#endif