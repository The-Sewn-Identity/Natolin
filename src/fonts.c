#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <raylib.h>
#include "fonts.h"
#include "util.h"

Font Haettenschweiler;
Font DokChampa;
Font Zaklad;
Font ModernDOS;

const FontData font_list[] = {
    {&Haettenschweiler, "HATTEN"},
    {&DokChampa, "dokchampa"},
    {&Zaklad, "Zaklad-Regular"},
    {&ModernDOS, "ModernDOS8x14"}
};
const unsigned int font_list_len = ARRAYSIZE(font_list);

void FontsLoad(void) {
    for (int i=0; i < font_list_len; i++) {
        const char * path = TextFormat("%s%s%s", "assets/fonts/", font_list[i]._name, ".ttf");

        *font_list[i]._font = LoadFontEx(path, DEFAULT_FONT_SIZE, 0, 0x4ff);
    }
}


void FontsUnload(void) {
    for (int i=0; i < font_list_len; i++) {
        UnloadFont(*font_list[i]._font);
    }
}