#pragma once
#include "../core.h"
#include "../Draw.h"
void DrawPixel(SDL_Renderer* renderer, int x, int y, vec3 color) {
	SDL_SetRenderDrawColor(renderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), SDL_ALPHA_OPAQUE);
	SDL_Point point;
	point.x = x;
	point.y = y;
	SDL_RenderDrawPoints(renderer, &point, 1);
}

void DrawTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2, vec3 color) {
	 // 按 y 排序顶点，v0.y <= v1.y <= v2.y
     if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }
     if (y0 > y2) { std::swap(x0, x2); std::swap(y0, y2); }
     if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
 
     // 设置颜色
     SDL_SetRenderDrawColor(renderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), 255);
 
     auto edge_interp = [](int x0, int y0, int x1, int y1, int y) -> float {
         if (y1 == y0) return x0;
         return x0 + (x1 - x0) * ((float)(y - y0) / (float)(y1 - y0));
     };
 
     for (int y = y0; y <= y2; ++y) {
         bool lower = y < y1 || y1 == y0;
 
         float xA = 0.0f, xB = 0.0f;
 
         if (y < y1) {
             // 下半三角形
             xA = edge_interp(x0, y0, x2, y2, y);
             xB = edge_interp(x0, y0, x1, y1, y);
         } else {
             // 上半三角形
             xA = edge_interp(x0, y0, x2, y2, y);
             xB = edge_interp(x1, y1, x2, y2, y);
         }
 
         if (xA > xB) std::swap(xA, xB);
 
         // 画扫描线
         for (int x = (int)xA; x <= (int)xB; ++x) {
             SDL_RenderDrawPoint(renderer, x, y);
         }
     }
}

vec3 CalcBarycentric(float x0, float y0, float x1, float y1, float x2, float y2, float px, float py) {
	float Ux = x1 - x0;
	float Uy = y1 - y0;
	float Vx = x2 - x0;
	float Vy = y2 - y0;
	float POx = x0 - px;
	float POy = y0 - py;

	vec3 kAB1 = cross(vec3(Ux, Vx, POx), vec3(Uy, Vy, POy));
	
	if (abs(kAB1.z) < 1.0f)                           
		return vec3(-1.0f, 1.0f, 1.0f);

	float A = kAB1.x / kAB1.z;
	float B = kAB1.y / kAB1.z;
	return vec3(1.0f - A - B, A, B);
}

void DrawTriangleBarycentric(SDL_Renderer* renderer, V2F v0, V2F v1, V2F v2) {  
// 计算三角形的包围盒
int minX = std::min({v0.posV2P.x, v1.posV2P.x, v2.posV2P.x});
int maxX = std::max({v0.posV2P.x, v1.posV2P.x, v2.posV2P.x});
int minY = std::min({v0.posV2P.y, v1.posV2P.y, v2.posV2P.y});
int maxY = std::max({v0.posV2P.y, v1.posV2P.y, v2.posV2P.y});

for (int y = minY; y <= maxY; ++y) {
    for (int x = minX; x <= maxX; ++x) {
        vec3 bary = CalcBarycentric(v0.posV2P.x, v0.posV2P.y, v1.posV2P.x, v1.posV2P.y, v2.posV2P.x, v2.posV2P.y, x, y);
        if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0) {
            // 插值颜色
            vec3 color = bary.x * v0.color + bary.y * v1.color + bary.z * v2.color;
            DrawPixel(renderer, x, y, color);
        }
    }
}
}
