#ifndef INTERFACE_H
#define INTERFACE_H

// MRB - Main Render Box, if it's that hard for you to remember
// nevermind

#define RENDERBOXWIDTH 480
#define RENDERBOXHEIGHT 320
extern RenderTexture2D playbox;
extern RenderTexture2D bars;
extern Texture2D barstex;

void CreatePlayBox();
void UnloadPlayBox();
void DrawPlayBox();

void CreateInterface();
void UnloadInterface();
void DrawInterface();

int GetRenderCenterX();
int GetRenderCenterY();

#endif