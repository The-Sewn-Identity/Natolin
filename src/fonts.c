#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "fonts.h"
#include "util.h"

Font Haettenschweiler;
Font DokChampa;
Font Zaklad;
FontData * fl_ptr;
unsigned int * font_list_len;

void FontsLoad(void) {
    FontData font_list[] = {
        {&Haettenschweiler, "HATTEN"},
        {&DokChampa, "dokchampa"},
        {&Zaklad, "Zaklad-Regular"}
    };
    unsigned int length = ARRAYSIZE(font_list);
    font_list_len = &length;
    fl_ptr = font_list;

    for (int i=0; i < *font_list_len; i++) {
        *fl_ptr[i]._font = LoadFontEx(TextFormat(
            "%s%s%s", "assets/fonts/", fl_ptr[i]._name, ".ttf"), DEFAULT_FONT_SIZE, NULL, 0);
    }
}

void FontsUnload(void) {
    for (int i=0; i < *font_list_len; i++) {
        // UnloadFont(*fl_ptr[i]._font);
    }
}