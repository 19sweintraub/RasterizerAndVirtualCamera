#include<camera.h>
#include<glm/gtc/matrix_transform.hpp>

Camera::Camera() : fVec(glm::vec4(0, 0, -1, 0)), rVec(glm::vec4(1, 0, 0, 0)),
    uVec(glm::vec4(0, 1, 0, 0)), fov(45), camW(glm::vec4(0, 0, 10, 1)),
    n(0.01), f(100), aspect(1) {}

glm::mat4 Camera::viewMat() {
    glm::vec4 col1 = glm::vec4(rVec[0], uVec[0], fVec[0], 0);
    glm::vec4 col2 = glm::vec4(rVec[1], uVec[1], fVec[1], 0);
    glm::vec4 col3 = glm::vec4(rVec[2], uVec[2], fVec[2], 0);
    glm::vec4 col4 = glm::vec4(0, 0, 0, 1);
    glm::mat4 O = glm::mat4(col1, col2, col3, col4);
    glm::mat4 T = glm::mat4(1);
    T[3] = glm::vec4(-camW[0], -camW[1], -camW[2], 1);
    // glm::mat4 test = O*T;
    return O*T;
}

glm::mat4 Camera::projMat() {
    glm::vec4 col1 = glm::vec4((1/(aspect*tan(fov/2))), 0, 0, 0);
    glm::vec4 col2 = glm::vec4(0, (1/tan(fov/2)), 0, 0);
    glm::vec4 col3 = glm::vec4(0, 0, (f/(f-n)), 1);
    glm::vec4 col4 = glm::vec4(0, 0, (-f*n)/(f-n), 0);
    return glm::mat4(col1, col2, col3, col4);
}

void Camera::moveF(float x) {
    camW += x*fVec;
}

void Camera::moveR(float y) {
    camW += y*rVec;
}

void Camera::moveU(float z) {
    camW += z*uVec;
}

void Camera::rotCamF(float a) {
    glm::mat4 model = glm::rotate(glm::mat4(1), -a, glm::vec3(fVec[0], fVec[1], fVec[2]));

    uVec = model * uVec;
    rVec = model * rVec;
}

void Camera::rotCamR(float b) {
    glm::mat4 model = glm::rotate(glm::mat4(1), -b, glm::vec3(rVec[0], rVec[1], rVec[2]));

    uVec = model * uVec;
    fVec = model * fVec;
}

void Camera::rotCamU(float g) {
    glm::mat4 model = glm::rotate(glm::mat4(1), -g, glm::vec3(uVec[0], uVec[1], uVec[2]));

    rVec = model * rVec;
    fVec = model * fVec;
}


