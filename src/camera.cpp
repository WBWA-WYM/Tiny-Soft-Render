    #include "../camera.h"


    glm::mat4x4 maincamera::getViewMatrix(glm::vec3 camPos, glm::vec3 tarPos, glm::vec3 up)
    {
        mViewMatrix = glm::lookAt(camPos,tarPos,up);
        return mViewMatrix;
    }

    glm::mat4x4 maincamera::getProjectionMatrix(float fovy, float aspect, float near, float far)
    {
        mProjectionMatrix = glm::perspective(fovy,aspect,near,far);
        return mProjectionMatrix;
    }

    
    void maincamera::updateCamera()
    {
    // 计算绕 Y 轴的旋转角度（假设每秒旋转 45 度）
    float angle = glm::radians(45.0f)*0.05;

    // 创建绕 Y 轴的旋转矩阵
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    // 计算新的相机位置
    glm::vec3 direction = pos - goal;
    direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    pos = goal + direction;

    // 更新视图矩阵
    mViewMatrix = glm::lookAt(pos, goal, up);
    }

    maincamera::maincamera(glm::vec3 mpos, glm::vec3 mgoal, glm::vec3 mup, float mfov, float masp, float mnear, float mfar)
    {
        pos = mpos;
        goal = mgoal;
        up = mup;
        fov = mfov;
        asp = masp;
        near = mnear;
        far = mfar;
    }
