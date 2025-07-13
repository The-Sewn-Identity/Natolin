#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "interface.h"

#define SHORTDIR "assets/textures/player/%s/%s"

Player current_player;
int froms;

void LoadPlayerTextures(Texture2D ** _textures) {

}

void LoadPlayerAnimations(Texture2D ** _animations) {
    // 1st array - Idle animations
    // 4th array - Inspect animations
    _animations = malloc(2 * sizeof(Texture2D*));
    _animations[0] = malloc(sizeof(Texture2D));
    _animations[1] = malloc(sizeof(Texture2D));

    _animations[0][0] = (Texture2D){};
    _animations[1][0] = LoadTextureFromImage(
        LoadImageAnim("", &froms));
}

Player CreatePlayer(void) {
    Player pl = {
        .fname = "Stanisław",
        .lname = "Konieczny",
        .x_pos = GetRenderCenterX(),
        .y_pos = GetRenderCenterY(),
        .layer = 15,
        .offset_x = 0,
        .offset_y = 0,
        .ability = Inspect
    };
    LoadPlayerAnimations(pl.animations);

    return pl;
}

void UnloadPlayer(Player *__player) {

}

void AnimatePlayer(Player *__player) {

}

void Inspect(Player *__player) {
}