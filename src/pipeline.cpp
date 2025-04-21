#include "../pipeline.h"
#include "../core.h"
#include "../Draw.h"
#include <iostream>


Pipeline::~Pipeline()
{
    if(mShader)delete mShader;
    mShader = nullptr;
}

void Pipeline::initialize(maincamera *in)
{
    mShader = new BasicShader(in);
    setViewMatrix();
}

void Pipeline::clearBuffer(const glm::vec4 &color, bool depth,SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void Pipeline::setShaderMode(ShadingMode mode,maincamera* camera)
{
    if(mShader)delete mShader;
    if(mode == Simple){
        mShader = new BasicShader(camera);
    }
}

void Pipeline::drawIndex(RenderMode mode,maincamera* camera,SDL_Renderer* renderer)
{
    if(mIndices.empty())return;
    for(unsigned int i=0;i<mIndices.size()/3;i++)
    {   
        
        Vertex vv1=mVertices[mIndices[i*3]],vv2=mVertices[mIndices[i*3+1]],vv3=mVertices[mIndices[i*3+2]];
        V2F v1=mShader->vertexShader(vv1),v2=mShader->vertexShader(vv2),v3=mShader->vertexShader(vv3);
        //视锥剔除
        auto insideFrustum = [&](const V2F &v) {
            // 裁剪空间做齐次裁剪：x/w, y/w, z/w ∈ [-1,1]
            float ndcX = v.posV2P.x / v.posV2P.w;
            float ndcY = v.posV2P.y / v.posV2P.w;
            float ndcZ = v.posV2P.z / v.posV2P.w;
            return ndcX >= -1.0f && ndcX <= 1.0f &&
                   ndcY >= -1.0f && ndcY <= 1.0f &&
                   ndcZ >= -1.0f && ndcZ <= 1.0f;
        };
        // 如果三个顶点都在视锥外，则跳过光栅化
        if (!insideFrustum(v1) && !insideFrustum(v2) && !insideFrustum(v3)) {
            continue;  // 完全不可见，剔除 :contentReference[oaicite:1]{index=1}
        }


        //
        v1.posV2P = v1.posV2P/v1.posV2P.w;
        v2.posV2P = v2.posV2P/v2.posV2P.w;
        v3.posV2P = v3.posV2P/v3.posV2P.w;
        //
        v1.posV2P = viewPortMatrix*v1.posV2P;
        v2.posV2P = viewPortMatrix*v2.posV2P;
        v3.posV2P = viewPortMatrix*v3.posV2P;

        //屏幕空间背面剔除
        glm::vec2 s0(v1.posV2P.x, v1.posV2P.y);
        glm::vec2 s1(v2.posV2P.x, v2.posV2P.y);
        glm::vec2 s2(v3.posV2P.x, v3.posV2P.y);
        // 计算 2D 叉积的 Z 分量
        float crossZ = (s1.x - s0.x) * (s2.y - s0.y)
                    - (s1.y - s0.y) * (s2.x - s0.x);
        // 如果三角形以逆时针 (CCW) 定义为“面向”
        // 则当 crossZ <= 0 时剔除
        if (crossZ <= 0.0f) {
            continue;
        }


        if(mode==Wire)
        {
            
        }
        else if(mode==Fill)
        {
            // DrawTriangle(renderer,v1.posV2P.x,v1.posV2P.y,v2.posV2P.x,v2.posV2P.y,v3.posV2P.x,v3.posV2P.y,vec3(1.0f,0.7f,0.0f));
            DrawTriangleBarycentric(renderer,v1,v2,v3);
        }

    }

}

void Pipeline::setViewMatrix()
{
    glm::mat4 viewportMatrixTmp(1.0f);
    viewportMatrixTmp[0][0] =  width * 0.5f;
    viewportMatrixTmp[1][1] = -height * 0.5f;  // 翻转 Y
    viewportMatrixTmp[3][0] =  width * 0.5f;
    viewportMatrixTmp[3][1] =  height * 0.5f;
    viewPortMatrix = viewportMatrixTmp;
}
