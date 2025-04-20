#pragma once
#include "core.h"
#include "camera.h"
#include "v2f.h"
#include "vertex.h"
//Shader的抽象类，可包含顶点着色器和片元着色器
class Shader{
public:
    Shader(){}
    virtual ~Shader(){}
    virtual V2F vertexShader(const Vertex &in) = 0;
    virtual glm::vec4 fragmentShader(const V2F &in) = 0;
};
class BasicShader:public Shader
{
public:
    BasicShader(maincamera* in)
        :camera(in)
    {
        ModelMatrix = glm::mat4(1.0f);
        ViewMatirx = glm::mat4(1.0f);
        ProjectionMatirx = glm::mat4(1.0f);
    }
    ~BasicShader(){}
    V2F vertexShader(const Vertex &in) override;
    glm::vec4 fragmentShader(const V2F &in) override;
public:
    glm::mat4x4 ModelMatrix;
    glm::mat4x4 ViewMatirx;
    glm::mat4x4 ProjectionMatirx;
private:
    maincamera* camera;
};
