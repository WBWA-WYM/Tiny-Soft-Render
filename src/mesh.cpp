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
    // 8 个顶点（固定）
    glm::vec3 pos[8] = {
        {-h,-h,-h}, { h,-h,-h}, { h, h,-h}, {-h, h,-h},  // 后面 (Z−)
        {-h,-h, h}, { h,-h, h}, { h, h, h}, {-h, h, h}   // 前面 (Z+)
    };

    // **所有面都按 CCW 绕向定义**（从外部看时顶点逆时针）
    unsigned int idx[36] = {
        // 后面 (Z−)，看向 -Z 方向，CCW: 0→1→2, 0→2→3
        0, 1, 2,   0, 2, 3,
        // 前面 (Z+)，看向 +Z 方向，CCW: 4→6→5, 4→7→6
        4, 6, 5,   4, 7, 6,
        // 左面 (X−)，看向 -X 方向，CCW: 0→3→7, 0→7→4
        0, 3, 7,   0, 7, 4,
        // 右面 (X+)，看向 +X 方向，CCW: 1→5→6, 1→6→2
        1, 5, 6,   1, 6, 2,
        // 顶面 (Y+)，看向 +Y 方向，CCW: 3→2→6, 3→6→7
        3, 2, 6,   3, 6, 7,
        // 底面 (Y−)，看向 -Y 方向，CCW: 0→4→5, 0→5→1
        0, 4, 5,   0, 5, 1
    };

    vertices.resize(8);
    index.assign(idx, idx + 36);

    for (int i = 0; i < 8; ++i) {
        vertices[i].position = glm::vec4(pos[i] + glm::vec3(positionOffset), 1.0f);
        // 简单法线，用面中心法线更精确但可按此简化
        vertices[i].normal   = glm::normalize(pos[i]);
        // UV 简化：按 x/y 分配
        vertices[i].texcoord = { (pos[i].x > 0.0f) ? 1.0f : 0.0f,
                                 (pos[i].y > 0.0f) ? 1.0f : 0.0f };
        // 示例：给每个立方体一个颜色属性，便于调试
        vertices[i].color    = glm::vec4(0.8f, 0.2f, 0.2f, 1.0f);
    }
}

void Mesh::plane(float width, float height, int textureID, glm::vec4 positionOffset)
{
    float w2 = width * 0.5f;
    float h2 = height * 0.5f;

    vertices.clear();
    index = {0, 1, 2, 0, 2, 3};

    // 顶点位置 (X,Z平面)，法线 +Y，UV
    Vertex v0, v1, v2, v3;

    v0.position = glm::vec4(-w2, 0.0f, -h2, 1.0f);
    v0.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v0.texcoord = glm::vec2(0.0f, 0.0f);
    v0.color    = glm::vec4(1.0f);

    v1.position = glm::vec4( w2, 0.0f, -h2, 1.0f);
    v1.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v1.texcoord = glm::vec2(1.0f, 0.0f);
    v1.color    = glm::vec4(1.0f);

    v2.position = glm::vec4( w2, 0.0f,  h2, 1.0f);
    v2.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v2.texcoord = glm::vec2(1.0f, 1.0f);
    v2.color    = glm::vec4(1.0f);

    v3.position = glm::vec4(-w2, 0.0f,  h2, 1.0f);
    v3.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v3.texcoord = glm::vec2(0.0f, 1.0f);
    v3.color    = glm::vec4(1.0f);

    // 整体平移
    v0.position += positionOffset;
    v1.position += positionOffset;
    v2.position += positionOffset;
    v3.position += positionOffset;

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
}
