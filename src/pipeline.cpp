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

        //
        v1.posV2P = v1.posV2P/v1.posV2P.w;
        v2.posV2P = v2.posV2P/v2.posV2P.w;
        v3.posV2P = v3.posV2P/v3.posV2P.w;
        //
        v1.posV2P = viewPortMatrix*v1.posV2P;
        v2.posV2P = viewPortMatrix*v2.posV2P;
        v3.posV2P = viewPortMatrix*v3.posV2P;

        if(mode==Wire)
        {
            
        }
        else if(mode==Fill)
        {
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
