#include <raylib.h>
#include <stdio.h>
#include "system_defs.h"
#include "extutil.h"

enum AspectRatios currentAspectRatio;

void SetCurrentAspectRatio(void) {
    int ratio[2] = { 
        GetScreenWidth() / nwd(GetScreenWidth(), GetScreenHeight()),
        GetScreenHeight() / nwd(GetScreenWidth(), GetScreenHeight())
    };

    if (ratio[0] == 4 && ratio[1] == 3) {
        currentAspectRatio = ASPECT_RATIO_STANDARD;
    }
    else if (ratio[0] == 16 && ratio[1] == 9) {
        currentAspectRatio = ASPECT_RATIO_WIDESCREEN_16x9;
    }
    else if (ratio[0] == 8 && ratio[1] == 5) {
        currentAspectRatio = ASPECT_RATIO_WIDESCREEN_16x10;
    }
    else {
        currentAspectRatio = ASPECT_RATIO_STANDARD;
    }
}

void FollowMouse(void) {
    
}