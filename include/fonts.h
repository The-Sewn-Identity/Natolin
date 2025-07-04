#ifndef FONTS_H
#define FONTS_H

#define DEFAULT_FONT_SIZE 96
#define DEFAULT_SPACING 1

typedef struct FontData {
    Font* _font;
    char* _name;
} FontData;

extern Font Haettenschweiler;
extern Font DokChampa;
extern Font Zaklad;
void FontsLoad(void);
void FontsUnload(void);

#endif