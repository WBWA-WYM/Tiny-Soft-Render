#pragma once
#include "core.h"
class maincamera
{
public:
    glm::vec3 pos,goal,up;
    float fov,asp,near,far;
public:
    maincamera(glm::vec3 mpos,glm::vec3 mgoal,glm::vec3 mup,
               float mfov,float masp,float mnear,float mfar);
    void rotateY(float angle);
    void updateCamera();
    glm::mat4x4 getViewMatrix(glm::vec3 camPos,glm::vec3 tarPos,glm::vec3 up);
    glm::mat4x4 getProjectionMatrix(float fovy, float aspect, float near, float far);
    glm::mat4x4 mViewMatrix;
    glm::mat4x4 mProjectionMatrix;
};