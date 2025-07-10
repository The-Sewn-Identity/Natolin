#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    Texture2D ** textures;
    Texture2D ** animations;
    char * fname;
    char * lname;
    short int x_pos; // wahhh wahhh
    short int y_pos; 
    short offset_x; // wehhh wehhhhh
    short offset_y;
    void (*ability)(struct Player *);
} Player;
extern Player current_player;

Player CreatePlayer(void);

void AnimatePlayer(Player *__player);
void Inspect(Player *__player);

#endif