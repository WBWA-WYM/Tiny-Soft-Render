#include "v2f.h"
#include "vertex.h"
#include "shader.h"
#include <vector>
#include "camera.h"
#include <iostream>

class Pipeline
{
public:
    enum ShadingMode{Simple,Gouraud,Phong};
    enum RenderMode{Wire,Fill};
private:
    int width,height;
    Shader *mShader;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int>mIndices;
    glm::mat4x4 viewPortMatrix;
    maincamera* camera;
public:
    Pipeline(int w,int h):width(w),height(h)
    {};
    ~Pipeline();

    void initialize(maincamera* in);
    //setters
    void setVertexBuffer(const std::vector<Vertex> &vertices){mVertices = vertices;}
    void setIndexBuffer(const std::vector<unsigned int> &indices){mIndices = indices;}
    void setViewMatrix();


    void setShaderMode(ShadingMode mode,maincamera* camera);
    void drawIndex(RenderMode mode,maincamera* camera,SDL_Renderer* renderer);
    void swapBuffer();
    V2F  lerp(const V2F &n1,const V2F &n2,float weight);
    void bresenham(const V2F &from, const V2F &to);
    void swap(float &x, float &y);
    void scanLinePerRow(const V2F &left, const V2F &right);
    void rasterTopTriangle(V2F &v1, V2F &v2, V2F &v3);
    void rasterBottomTriangle(V2F &v1, V2F &v2, V2F &v3);
    void edgeWalkingFillRasterization(const V2F &v1, const V2F &v2, const V2F &v3);
    void clearBuffer(const glm::vec4 &color, bool depth,SDL_Renderer* renderer);
};


