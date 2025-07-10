#include <raylib.h>
#include <stdio.h>
#include "util.h"

//Texture2D LoadGIFAnim(const char * fileName) {}

float GetRTWidth(RenderTexture2D * _rndtex) {
    return (_rndtex->texture.width);
}

float GetRTHeight(RenderTexture2D * _rndtex) {
    return (_rndtex->texture.height);
}