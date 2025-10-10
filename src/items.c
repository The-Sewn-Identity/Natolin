#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "items.h"

Item CreateItem(unsigned int type, char * name, char * filename) {
    Item retitem;
    
    retitem.name = name;
    retitem.item_type = type;

    switch (type) {
        case STANDARD:
            break;
        case STORY:
            break;
        default:
            retitem.item_type = STANDARD;
            break;
    }

    retitem.menutex = LoadTexture(TextFormat("assets/textures/%s.png", filename));

    retitem.function = NULL;

    return retitem;
}