#ifndef INTERFACE_H
#define INTERFACE_H

#define RENDERBOXWIDTH 480
#define RENDERBOXHEIGHT 320
extern RenderTexture2D playbox;
extern RenderTexture2D bars;
extern RenderTexture2D inventory;
extern Texture2D bars_tex;
extern Texture2D inventory_tex;

void CreateInterface(void);
void UnloadInterface(void);

void DrawPlaybox(void);
void DrawPanel(void);
void DrawInventory(void);

#endif