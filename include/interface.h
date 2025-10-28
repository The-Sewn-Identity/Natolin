#ifndef INTERFACE_H
#define INTERFACE_H

#include "util.h"

#define RENDERBOXWIDTH 480
#define RENDERBOXHEIGHT 320
typedef struct Playbox {
    RenderTexture2D rendertex;
    Vector2 position;
} Playbox;
extern Playbox playbox;

extern RenderTexture2D panel;
extern RenderTexture2D inventory;
extern RenderTexture2D interface;
extern Texture2D panel_tex;
extern Texture2D inventory_tex;

typedef struct IButton {
    Texture2D tex_arr[2];
    Vector2 vect;
    char * name;
    bool state;
    void (*func)(void *);
} IButton;

void CreateInterface(void);
void DrawInterface(void);
void UnloadInterface(void);

void DrawPlaybox(void);
void DrawPanel(void);
void DrawInventory(void);

#endif