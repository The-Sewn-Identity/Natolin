#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "items.h"

Item CreateItem(unsigned int type, char * name, char * fileName) {
    Item retitem;
    
    switch (type) {
        case STANDARD:
            break;
        case STORY:
            break;
        default:
            break;
    }

    Texture2D menutex = LoadTexture(TextFormat(fileName));
    return (Item){menutex, type, name, NULL};
}