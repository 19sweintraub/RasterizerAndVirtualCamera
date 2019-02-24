#include<lineseg2d.h>

Lineseg2D::Lineseg2D(glm::vec4 endPoint1, glm::vec4 endPoint2) : p1(endPoint1[0], endPoint1[1]),
p2(endPoint2[0], endPoint2[1]) {

    // assumes m_pos is a float so that divsion by zero returns infinity
    slope = (p2[1] - p1[1]) / (p2[0] - p1[0]);
}

bool Lineseg2D::xIntersect(float y, std::vector<float>* intersects, float minX, float maxX) {
    if ( (y >= std::max({p1[1], p2[1]})) || (y <= std::min({p1[1], p2[1]})) ) {
        return false;
    }
    if (std::isinf(slope)) {
        intersects->push_back(p1[0]);
        return true;
    } else if (slope == 0) {
        return false;
    } else {
        float x = (y + slope*p1[0] - p1[1]) / slope;
        intersects->push_back(x);
        return true;
    }
}
