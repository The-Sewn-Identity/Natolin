#ifndef ITEMS_H
#define ITEMS_H

enum ItemType {
    STANDARD,
    STORY
};

typedef struct Item {
    Texture2D menutex;
    unsigned int item_type;
    char * name;
    void (* function)();
} Item;

Item CreateItem(unsigned int type, char * name, char * filename);

#endif