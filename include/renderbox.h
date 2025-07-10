#ifndef RENDERBOX_H
#define RENDERBOX_H

// MRB - Main Render Box, if it's that hard for you to remember
// nevermind

#define RENDERBOXWIDTH 480
#define RENDERBOXHEIGHT 320
extern RenderTexture2D renderbox;

void CreateMainRenderBox();
void UnloadMainRenderBox();
void DrawMainRenderBox();

int GetRenderCenterX();
int GetRenderCenterY();

#endif