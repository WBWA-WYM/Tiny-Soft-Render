#pragma once
#include "core.h"

class Vertex
{
public:
    glm::vec4 position;
    glm::vec4 color;
    glm::vec2 texcoord;
    glm::vec3 normal;

    Vertex() = default;            // 内联默认构造
    ~Vertex() = default;           // 内联默认析构
    Vertex(
        glm::vec4 pos,
        glm::vec4 co,
        glm::vec2 tex,
        glm::vec3 nor
        ):position(pos),color(co),texcoord(tex),normal(nor){}

    Vertex(const Vertex &ver):position(ver.position),color(ver.color),texcoord(ver.texcoord),normal(ver.normal){}
};

