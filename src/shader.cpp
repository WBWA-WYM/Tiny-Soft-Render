#include "../shader.h"


V2F BasicShader::vertexShader(const Vertex &in)
{
    V2F ret;

    //set MVP
    ViewMatirx = camera->getViewMatrix(camera->pos,camera->goal,camera->up);
    ModelMatrix = glm::mat4(1.0f);
    ProjectionMatirx = camera->getProjectionMatrix(camera->fov,camera->asp,camera->near,camera->far);

    vec4 tmp = vec4(in.position.x, in.position.y, in.position.z, 1.0f);
    // 模型空间 → 世界空间
    ret.posM2W = ModelMatrix * tmp;
    
    // 世界空间 → 裁剪空间
    ret.posV2P  = ProjectionMatirx * ViewMatirx * ret.posM2W;

    ret.oneDivZ  = 1.0f / ret.posV2P.w;

    ret.color = in.color;
    ret.normal = in.normal;
    ret.texcoord = in.texcoord;

    return ret;

}

glm::vec4 BasicShader::fragmentShader(const V2F &in)
{
    glm::vec4 retColor;
    retColor = in.color;
    return retColor;
}


