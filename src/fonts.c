#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "fonts.h"
#include "util.h"

Font Haettenschweiler;
FontData * font_list;
unsigned int font_list_len;

void FontsLoad() {
    font_list = (FontData []){
        (FontData){&Haettenschweiler, "HATTEN"}
    };

    font_list_len = ARRAYSIZE(*font_list, FontData);
    for (int i=0; i < font_list_len; i++) {
        *font_list[i]._font = LoadFontEx(TextFormat(
            "%s%s%s", "assets/fonts/", font_list[i]._name, ".ttf"), DEFAULT_FONT_SIZE, NULL, 0);
    }
}

void FontsUnload() {
    for (int i=0; i < font_list_len; i++) {
        UnloadFont(*font_list[i]._font);
    }
}