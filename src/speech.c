#include <stdlib.h>
#include <raylib.h>
#include "speech.h"
#include "fonts.h"
#include "util.h"

void DrawTextbox(char *text, Vector2 position, unsigned int mode) {
    int width; int height;
    int locx = position.x; int locy = position.y;
    int border = 2;

    Vector2 textlen = MeasureTextEx(Haettenschweiler, text, DEFAULT_FONT_SIZE, DEFAULT_SPACING);
    width = textlen.x + 20; height = textlen.y + 20;
    
    switch (mode) {
        case NORMAL:
            break;
        case INFO:
            break;
        case SPEECH:
            break;
        case THOUGHT:
            break;
        case ACHIEVEMENT:
            break;
        default:
            break;
    }
    
    Rectangle outrect = (Rectangle){locx, locy, width, height};
    Rectangle inrect = (Rectangle){locx + border/2, locy + border/2, width - border, height - border};

    DrawRectangleRec(outrect, BLACK);
    DrawRectangleRec(inrect, WHITE);
    DrawTextEx(Haettenschweiler, text, (Vector2){locx, locy}, DEFAULT_FONT_SIZE, DEFAULT_SPACING, BLACK);
}