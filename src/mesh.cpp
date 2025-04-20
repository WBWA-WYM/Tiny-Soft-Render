#include "../mesh.h"
Mesh& Mesh::operator=(const Mesh &msh)
{
    vertices = msh.vertices;
    index = msh.index;
    return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
    vertices.resize(static_cast<unsigned long>(count));
    new(&vertices[0])std::vector<Vertex>(v,v + count);
}

void Mesh::setIndex(int* i, int count)
{
    index.resize(static_cast<unsigned long>(count));
    new(&index)std::vector<unsigned int>(i,i+count);
}
void Mesh::triangle(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3)
{
    vertices.resize(3);
    index.resize(3);
    vertices[0].position.x = v1.x;
    vertices[0].position.y = v1.y;
    vertices[0].position.z = v1.z;
    vertices[0].normal=glm::vec3(0.f,0.f,1.f);
    vertices[0].color=glm::vec4(1.f,0.f,0.f,1.f);
    vertices[0].texcoord=glm::vec2(0.f,0.f);

    vertices[1].position.x = v2.x;
    vertices[1].position.y = v2.y;
    vertices[1].position.z = v2.z;
    vertices[1].normal=glm::vec3(0.f,0.f,1.f);
    vertices[1].color=glm::vec4(0.f,1.f,0.f,1.f);
    vertices[1].texcoord=glm::vec2(1.f,0.f);

    vertices[2].position.x = v3.x;
    vertices[2].position.y = v3.y;
    vertices[2].position.z = v3.z;
    vertices[2].normal=glm::vec3(0.f,0.f,1.f);
    vertices[2].color=glm::vec4(0.f,0.f,1.f,1.f);
    vertices[2].texcoord=glm::vec2(0.5f,1.f);
    index[0]=0;
    index[1]=1;
    index[2]=2;
}
void Mesh::triangle(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3,glm::vec3 &v4)
{
    vertices.resize(4);
    index.resize(12);
    vertices[0].position.x = v1.x;
    vertices[0].position.y = v1.y;
    vertices[0].position.z = v1.z;
    vertices[0].normal=glm::vec3(0.f,0.f,1.f);
    vertices[0].color=glm::vec4(1.f,0.f,0.f,1.f);
    vertices[0].texcoord=glm::vec2(0.f,0.f);

    vertices[1].position.x = v2.x;
    vertices[1].position.y = v2.y;
    vertices[1].position.z = v2.z;
    vertices[1].normal=glm::vec3(0.f,0.f,1.f);
    vertices[1].color=glm::vec4(0.f,1.f,0.f,1.f);
    vertices[1].texcoord=glm::vec2(1.f,0.f);

    vertices[2].position.x = v3.x;
    vertices[2].position.y = v3.y;
    vertices[2].position.z = v3.z;
    vertices[2].normal=glm::vec3(0.f,0.f,1.f);
    vertices[2].color=glm::vec4(0.f,0.f,1.f,1.f);
    vertices[2].texcoord=glm::vec2(0.5f,1.f);

    vertices[3].position.x = v4.x;
    vertices[3].position.y = v4.y;
    vertices[3].position.z = v4.z;
    vertices[3].normal=glm::vec3(0.f,0.f,1.f);
    vertices[3].color=glm::vec4(0.f,0.f,1.f,1.f);
    vertices[3].texcoord=glm::vec2(0.5f,1.f);

    // 四个三角面
    // 面 0: v1, v2, v3
    index[0]=0; index[1]=1; index[2]=2;
    // 面 1: v1, v2, v4
    index[3]=0; index[4]=1; index[5]=3;
    // 面 2: v2, v3, v4
    index[6]=1; index[7]=2; index[8]=3;
    // 面 3: v3, v1, v4
    index[9]=2; index[10]=0; index[11]=3;

}
