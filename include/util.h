#ifndef UTIL_H
#define UTIL_H

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])
#define FREEPTR(ptr) (free(ptr), ptr = NULL)

// Texture2D LoadGIFAnim(const char * fileName);

float GetRTWidth(RenderTexture2D * _rndtex);
float GetRTHeight(RenderTexture2D * _rndtex);

#endif