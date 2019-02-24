#ifndef LINESEG2D_H
#define LINESEG2D_H

#endif // LINESEG2D_H

// check this
#include<polygon.h>

class Lineseg2D {
public:
    // constructor
    Lineseg2D(glm::vec4 endPoint1, glm::vec4 endPoint2);

    // stores line segements endpoints
    // probably should take in pointer
    glm::vec2 p1;
    glm::vec2 p2;

    // stores intersection points
    std::vector<float> intersects;

    // line segment slope
    float slope;

    // A function that computes the x-intersection of the line segment with a horizontal line based on the horizontal line's y-coordinate
    // Returns a boolean indicating whether or not the lines intersect at all, while using a pointer as a function input to write the x-intersection.
    bool xIntersect(float y, std::vector<float>* intersects, float minX, float maxX);

};

