#include <stdlib.h>
#include <raylib.h>
#include "speech.h"
#include "fonts.h"
#include "util.h"

void DrawTextbox(char *text, Vector2 position, unsigned int mode) {
    int width; int height;
    int locx = position.x; int locy = position.y;
    int border = 2;

    unsigned int font_size = 20;
    
    switch (mode) {
        case NORMAL:
            font_size = 72;
            border = 8;
            break;
        case INFO:
            font_size = 14;
            break;
        case SPEECH:
            font_size = 20;
            break;
        case THOUGHT:
            font_size = 20;
            break;
        case ACHIEVEMENT:
            font_size = 20;
            break;
        default:
            border = 2;
            break;
    }

    Vector2 textlen = MeasureTextEx(Haettenschweiler, text, font_size, DEFAULT_SPACING);
    width = textlen.x; height = textlen.y;
    
    Rectangle outrect = (Rectangle){locx - border/2, locy - border/2, width + border, height + border};
    Rectangle inrect = (Rectangle){locx, locy, width, height};

    DrawRectangleRec(outrect, BLACK);
    DrawRectangleRec(inrect, WHITE);
    DrawTextEx(Haettenschweiler, text, (Vector2){locx, locy}, font_size, DEFAULT_SPACING, BLACK);
}