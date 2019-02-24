#pragma once
#include <polygon.h>
#include <QImage>
#include <camera.h>

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;
public:
    Rasterizer(const std::vector<Polygon>& polygons);
    QImage RenderScene();
    void ClearScene();
    glm::vec3 baryWeight(const Polygon &poly, const Triangle &t, const glm::vec3 P);
    Camera cam;
};

float lenVec3(glm::vec3 v);
