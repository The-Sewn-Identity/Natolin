#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "items.h"

Item CreateItem(unsigned int type, char * name, char * filename) {
    Item retitem;
    
    switch (type) {
        case STANDARD:
            break;
        case STORY:
            break;
        default:
            break;
    }

    Texture2D menutex = LoadTexture(TextFormat(filename));
    return (Item){menutex, type, name, NULL};
}