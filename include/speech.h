#ifndef SPEECH_H
#define SPEECH_H

#include <raylib.h>

typedef struct Textbox {
    Rectangle rect;
    unsigned int mode;
} Textbox;

void DrawSpeechBox(void);

#endif