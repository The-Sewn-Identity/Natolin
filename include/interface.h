#ifndef INTERFACE_H
#define INTERFACE_H

#define RENDERBOXWIDTH 480
#define RENDERBOXHEIGHT 320
extern RenderTexture2D playbox;

extern RenderTexture2D panel;
extern RenderTexture2D inventory;
extern RenderTexture2D interface;
extern Texture2D panel_tex;
extern Texture2D inventory_tex;

void CreateInterface(void);
void DrawInterface(void);
void UnloadInterface(void);

void DrawPlaybox(void);
void DrawPanel(void);
void DrawInventory(void);

#endif