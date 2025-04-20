#pragma once
#include "core.h"
#include "v2f.h"
void DrawPixel(SDL_Renderer* renderer, int x, int y, vec3 color);

void DrawTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2, vec3 color);

vec3 CalcBarycentric(float x0, float y0, float x1, float y1, float x2, float y2, float px, float py);

void DrawTriangleBarycentric(SDL_Renderer* renderer,V2F v0, V2F v1, V2F v2);