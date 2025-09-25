#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "fonts.h"
#include "util.h"

Font Haettenschweiler;
Font DokChampa;
Font Zaklad;
Font ModernDOS;

FontData font_list[] = {
    {&Haettenschweiler, "HATTEN"},
    {&DokChampa, "dokchampa"},
    {&Zaklad, "Zaklad-Regular"},
    {&ModernDOS, "ModernDOS8x14"}
};
unsigned int font_list_len;

void FontsLoad(void) {
    font_list_len = ARRAYSIZE(font_list);

    for (int i=0; i < font_list_len; i++) {
        *font_list[i]._font = LoadFontEx(TextFormat(
            "%s%s%s", "assets/fonts/", font_list[i]._name, ".ttf"), DEFAULT_FONT_SIZE, NULL, 0);
    }
}

/* static void AddCodepointRange(Font *font, char *font_path, int start, int stop) {
    int range_size = start - stop + 1; int current_rsize = font->glyphCount;
    int codepoint_count = current_rsize + range_size;

    int * updated_codepoints = (int *)malloc(codepoint_count * sizeof(int));
    for (int i=0; i < current_rsize; i++) updated_codepoints[i] = font->glyphs->value;
    for (int i=current_rsize; i < codepoint_count; i++) updated_codepoints[i] = start + (i - current_rsize);

    UnloadFont(*font);
    *font = LoadFontEx(font_path, DEFAULT_FONT_SIZE, updated_codepoints, codepoint_count);

    FREEPTR(updated_codepoints);
}

void LoadCodepoints(void) {
    
} */

void FontsUnload(void) {
    //printf("%s", font_list[0]._name);
    for (int i=0; i < font_list_len; i++) {
        UnloadFont(*font_list[i]._font);
    }
}