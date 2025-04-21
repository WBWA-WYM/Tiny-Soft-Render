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

void Mesh::cube(float size, int textureID, glm::vec4 positionOffset)
{
    float h = size * 0.5f;
    // 8 个顶点
    glm::vec3 pos[8] = {
        {-h,-h,-h},{ h,-h,-h},{ h, h,-h},{-h, h,-h},
        {-h,-h, h},{ h,-h, h},{ h, h, h},{-h, h, h}
    };
    // 正常情况下，立方体六面共 12 个三角形，36 个索引
    unsigned int idx[36] = {
        0,1,2, 2,3,0,  // 后面
        4,5,6, 6,7,4,  // 前面
        0,4,7, 7,3,0,  // 左面
        1,5,6, 6,2,1,  // 右面
        3,2,6, 6,7,3,  // 上面
        0,1,5, 5,4,0   // 下面
    };

    vertices.resize(8);
    index.assign(idx, idx+36);
    for (int i = 0; i < 8; ++i) {
        vertices[i].position = glm::vec4(pos[i] + glm::vec3(positionOffset), 1.0f);
        // 简化：法线可按面重计算，这里先置为单位向量
        vertices[i].normal = glm::normalize(pos[i]);
        // UV 简化：根据顶点在立方体的哪一面再自定义
        vertices[i].texcoord = { (pos[i].x>0)?1.0f:0.0f, (pos[i].y>0)?1.0f:0.0f };
        vertices[i].color = glm::vec4(1.0f);
    }
}

void Mesh::plane(float width, float height, int textureID, glm::vec4 positionOffset)
{
    float w2 = width * 0.5f;
    float h2 = height * 0.5f;
    vertices.resize(4);
    index = {0,1,2,  0,2,3};

    // 顶点位置 (X,Z平面)，法线 +Y，UV
    vertices[0].position = { -w2, 0.0f, -h2, 1.0f };
    vertices[0].normal   = { 0.0f, 1.0f, 0.0f };
    vertices[0].texcoord = { 0.0f, 0.0f };

    vertices[1].position = {  w2, 0.0f, -h2, 1.0f };
    vertices[1].normal   = { 0.0f, 1.0f, 0.0f };
    vertices[1].texcoord = { 1.0f, 0.0f };

    vertices[2].position = {  w2, 0.0f,  h2, 1.0f };
    vertices[2].normal   = { 0.0f, 1.0f, 0.0f };
    vertices[2].texcoord = { 1.0f, 1.0f };

    vertices[3].position = { -w2, 0.0f,  h2, 1.0f };
    vertices[3].normal   = { 0.0f, 1.0f, 0.0f };
    vertices[3].texcoord = { 0.0f, 1.0f };

    // 整体平移
    for (auto &v : vertices) {
        v.position += positionOffset;
    }

    // 贴图 ID
    for (auto &v : vertices) {
        v.color = glm::vec4(1.0f); // 如果片元着色器需要 Color，可用 alpha 保存 textureID
        v.texcoord = v.texcoord;
    }
}
