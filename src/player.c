#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "interface.h"

#define SHORTDIR "assets/textures/player/%s/%s"

Player current_player;

void LoadPlayerTextures(Texture2D ** _textures) {

}

void LoadPlayerAnimations(Texture2D ** _animations) {
    // 1st array - Idle animations
    // 4th array - Inspect animations
    _animations[0][0] = (Texture2D){};
    _animations[3][0] = LoadTextureFromImage(
        LoadImageAnim("", NULL));
}

Player CreatePlayer(void) {
    Player pl = {
        .fname = "Stanisław",
        .lname = "Konieczny",
        .x_pos = GetRenderCenterX(),
        .y_pos = GetRenderCenterY(),
        .offset_x = 0,
        .offset_y = 0,
        .ability = Inspect
    };
    //LoadPlayerAnimations(pl.animations);

    return pl;
}

void AnimatePlayer(Player *__player) {

}

void Inspect(Player *__player) {
}