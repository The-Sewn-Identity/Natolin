#ifndef ITEMS_H
#define ITEMS_H

enum ItemType {
    STANDARD,
    STORY
};

typedef struct Item {
    Texture2D menutex;
    void (* function)();
    char * name;
    short itemType;
} Item;

#endif