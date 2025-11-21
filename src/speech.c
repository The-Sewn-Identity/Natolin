#include <stdlib.h>
#include <raylib.h>
#include "speech.h"
#include "fonts.h"
#include "util.h"

void DrawTextbox(char *text, Vector2 position, unsigned int mode) {
    int width; int height;
    int loc_x = position.x; int loc_y = position.y;
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
    
    Rectangle outrect = (Rectangle){loc_x - border/2, loc_y - border/2, width + border, height + border};
    Rectangle inrect = (Rectangle){loc_x, loc_y, width, height};

    DrawRectangleRec(outrect, BLACK);
    DrawRectangleRec(inrect, WHITE);
    DrawTextEx(Haettenschweiler, text, (Vector2){loc_x, loc_y}, font_size, DEFAULT_SPACING, BLACK);
}