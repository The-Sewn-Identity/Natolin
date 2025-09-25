#include <raylib.h>
#include <stdio.h>
#include "system_defs.h"
#include "extutil.h"

int currentAspectRatio;

int * CheckAspectRatio() {
    static int ar[2];

    ar[0] = GetScreenWidth() / nwd(GetScreenWidth(), GetScreenHeight());
    ar[1] = GetScreenHeight() / nwd(GetScreenWidth(), GetScreenHeight());

    return ar;
}

void SetCurrentAspectRatio(void) {
    int * ratio = CheckAspectRatio();

    if (ratio[0] == 4 && ratio[1] == 3) {
        currentAspectRatio = ASPECT_RATIO_STANDARD;
    }
    else if (ratio[0] == 16 && ratio[1] == 9) {
        currentAspectRatio = ASPECT_RATIO_WIDESCREEN_16x9;
    }
    else if (ratio[0] == 8 && ratio[1] == 5) {
        currentAspectRatio = ASPECT_RATIO_WIDESCREEN_16x10;
    }
}