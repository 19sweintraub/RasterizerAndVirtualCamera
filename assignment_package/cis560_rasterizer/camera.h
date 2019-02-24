#ifndef CAMERA_H
#define CAMERA_H

#endif // CAMERA_H

#include<polygon.h>

class Camera {
public:

    // cameras forward, right, and upward vector
    glm::vec4 fVec;
    glm::vec4 rVec;
    glm::vec4 uVec;

    // field of view
    float fov;

    // camera postion in world space
    glm::vec4 camW;

    // near clip
    float n;
    // far clip
    float f;

    // aspect ratio
    float aspect;

    // constructor
    Camera();

    glm::mat4 viewMat();
    glm::mat4 projMat();

    void moveF(float x);
    void moveR(float y);
    void moveU(float z);

    void rotCamF(float a);
    void rotCamR(float b);
    void rotCamU(float g);
};
