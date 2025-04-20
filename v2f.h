#pragma once 
#include "core.h"

class V2F
{
public:
    V2F() = default;
    ~V2F() = default;

    glm::vec4 posM2W;
    glm::vec4 posV2P;
    glm::vec2 texcoord;
    glm::vec3 normal;
    glm::vec4 color;
    int textureID;
    double oneDivZ;
    V2F(glm::vec4 pMW, glm::vec4 pVP, glm::vec2 tex,glm::vec3 nor, glm::vec4 col, double oZ):
        posM2W(pMW),posV2P(pVP),texcoord(tex),normal(nor),color(col),oneDivZ(oZ) {}
    V2F(const V2F& ver):
        posM2W(ver.posM2W),
        posV2P(ver.posV2P),
        texcoord(ver.texcoord),
        normal(ver.normal),
        color(ver.color),
        oneDivZ(ver.oneDivZ){}
    glm::vec4 Lerp(glm::vec4 &v1, glm::vec4 &v2,float weight){
        glm::vec4 vv1 = v1;
        glm::vec4 vv2 = v2;
        return vv1*(1.0f-weight) + weight*vv2;
    }
    glm::vec3 Lerp(const glm::vec3 &v1,const glm::vec3 &v2,float weight){
        return (1.0f-weight)*v1 + weight*v2;
    }
    glm::vec2 Lerp(const glm::vec2 &v1,const glm::vec2 &v2,float weight){
        return (1.0f-weight)*v1 + weight*v2;
    }
    void Lerp(const V2F &v1,const V2F &v2,float weight){
        this->color = (1-weight)*v1.color + weight*v2.color;
        this->normal = (1-weight)*v1.normal + weight*v2.normal;
        this->posV2P = (1-weight)*v1.posV2P + weight*v2.posV2P;
        this->oneDivZ = (1-weight)*v1.oneDivZ + weight*v2.oneDivZ;
        this->posM2W = (1-weight)*v1.posM2W + weight*v2.posM2W;
        this->texcoord = (1-weight)*v1.texcoord + weight*v2.texcoord;
    }
};


