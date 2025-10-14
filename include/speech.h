#ifndef SPEECH_H
#define SPEECH_H

#include <raylib.h>

enum TextboxModes {
    NORMAL,
    INFO,
    SPEECH,
    THOUGHT,
    ACHIEVEMENT
};

void DrawTextbox(char *text, Vector2 position, unsigned int mode);

#endif