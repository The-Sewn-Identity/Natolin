#ifndef SYSTEM_DEFS_H
#define SYSTEM_DEFS_H

typedef enum {
    ASPECT_RATIO_STANDARD,
    ASPECT_RATIO_WIDESCREEN_16x9,
    ASPECT_RATIO_WIDESCREEN_16x10
} AspectRatios;
extern short currentAspectRatio;

void SetCurrentAspectRatio(void);

#endif