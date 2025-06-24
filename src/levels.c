#include <stdio.h>
#include <lslread.h>
#include "levels.h"

LSL_Layout * level_01;

void LoadLevels() {
    LSL_Layout L01 = ReadMap("assets/levels/level01.lsl");
    level_01 = &L01;
    for (int l=0; l < 64; l++) {
        for (int n=0; n < 128; n++) {
            printf("%s", level_01->layers[l][n].image);
        }
    }
}