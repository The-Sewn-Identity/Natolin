#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "fonts.h"
#include "util.h"

Font Haettenschweiler;
Font DokChampa;
Font Zaklad;

FontData font_list[] = {
    {&Haettenschweiler, "HATTEN"},
    {&DokChampa, "dokchampa"},
    {&Zaklad, "Zaklad-Regular"}
};
unsigned short font_list_len;

void FontsLoad(void) {
    font_list_len = ARRAYSIZE(font_list);

    for (int i=0; i < font_list_len; i++) {
        *font_list[i]._font = LoadFontEx(TextFormat(
            "%s%s%s", "assets/fonts/", font_list[i]._name, ".ttf"), DEFAULT_FONT_SIZE, NULL, 0);
    }
}

void FontsUnload(void) {
    //printf("%s", font_list[0]._name);
    for (int i=0; i < font_list_len; i++) {
        UnloadFont(*font_list[i]._font);
    }
}