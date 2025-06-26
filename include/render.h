#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include <lslread.h>

typedef Texture2D LSL_Texture_Container[64][128];

LSL_Texture_Container * CreateLSLTextCont(LSL_Layout * layout);

void RenderLSL(LSL_Texture_Container * tex_cont);
void FreeLSLTextCont(LSL_Texture_Container * tex_cont);

#endif