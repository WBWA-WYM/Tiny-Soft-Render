#pragma once
#include "core.h"
#include <vector>
#include "vertex.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> index;

    Mesh(){}
    ~Mesh(){}

    Mesh(const Mesh& msh):vertices(msh.vertices),index(msh.index){}
    Mesh& operator=(const Mesh& msh);
    void setVertices(Vertex* v, int count);
    void setIndex(int* i, int count);

    void triangle(glm::vec3 &v1,glm::vec3 &v2,glm::vec3 &v3);
    void triangle(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3,glm::vec3 &v4);
    void pyramid();
    void cube(double width, double height, double depth, int id, glm::vec4 pos);
    void plane(double width,double height,int id,glm::vec4 pos);
};
