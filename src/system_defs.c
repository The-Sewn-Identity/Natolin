#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "system_defs.h"
#include "extutil.h"

enum AspectRatios currentAspectRatio;
int ratio[2];
float ratioScale;

void SetCurrentAspectRatio(void) {
    ratio[0] = GetScreenWidth() / nwd(GetScreenWidth(), GetScreenHeight());
    ratio[1] = GetScreenHeight() / nwd(GetScreenWidth(), GetScreenHeight());
    ratioScale = floorf( ((float)ratio[0] / ratio[1]) * 100) / 100;

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
    // zmień to na skalowe i potem stosunkowe
}

void FollowMouse(void) {
    
}