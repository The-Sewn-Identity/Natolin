#include <stdio.h>
#include <lslread.h>
#include "levels.h"

LSL_Layout level_01;

void LoadLevels(void) {
    level_01 = ReadMap("assets/levels/Pax-Congress.lsl");
}