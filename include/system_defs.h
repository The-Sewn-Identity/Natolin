#ifndef SYSTEM_DEFS_H
#define SYSTEM_DEFS_H

enum AspectRatios {
    ASPECT_RATIO_STANDARD,
    ASPECT_RATIO_WIDESCREEN_16x9,
    ASPECT_RATIO_WIDESCREEN_16x10,
    ASPECT_RATIO_COUNT
};
extern enum AspectRatios currentAspectRatio;
extern int ratio[2]; extern float ratioScale;

void SetCurrentAspectRatio(void);
void FollowMouse(void);

#endif