#ifndef ITEMS_H
#define ITEMS_H

enum ItemType {
    STANDARD,
    STORY
};

typedef struct Item {
    Texture2D menutex;
    short item_type;
    char * name;
    void (* function)();
} Item;

#endif