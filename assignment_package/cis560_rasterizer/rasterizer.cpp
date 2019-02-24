#include "rasterizer.h"
#include<lineseg2d.h>
#include <iostream>
#include<glm/glm.hpp>
#include<array>

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons), cam(Camera())
{}

QImage Rasterizer::RenderScene()
{
    // TODO: Complete the various components of code that make up this function
    // It should return the rasterized image of the current scene

    // Notice that even though it should return a QImage this function compiles.
    // Remember, C++'s compiler is dumb (though it will at least warn you that
    // the function doesn't return anything).
    // BEWARE! If you use a function that is missing its return statement,
    // it will return garbage memory!

    QImage im = QImage(512, 512, QImage::Format_RGB32);
    im.fill(Qt::black);

    float zBuffer[512*512];
    for (int i = 0; i < (512*512) ; i++) {
        zBuffer[i] = std::numeric_limits<float>::max();
    }

    // for each polygon
    for (Polygon& poly : m_polygons) {

        // transform coordinates
        for (Vertex& v : poly.m_verts) {

            v.m_spos = cam.projMat() * cam.viewMat() * v.m_pos;
            v.m_spos /= v.m_spos[3];
            v.m_spos[0] = ((v.m_spos[0] + 1) / 2) * 512;
            v.m_spos[1] = ((1 - v.m_spos[1]) / 2) * 512;
        }


        // for each triangle
        for (Triangle& tri : poly.m_tris) {

            // generate line segments
            Vertex v1 = poly.m_verts[tri.m_indices[0]];
            Vertex v2 = poly.m_verts[tri.m_indices[1]];
            Vertex v3 = poly.m_verts[tri.m_indices[2]];

            // Make Bounding Box
            float bbMinX = std::min({poly.m_verts[tri.m_indices[0]].m_spos[0], poly.m_verts[tri.m_indices[1]].m_spos[0], poly.m_verts[tri.m_indices[2]].m_spos[0]});
            float bbMinY = std::min({poly.m_verts[tri.m_indices[0]].m_spos[1], poly.m_verts[tri.m_indices[1]].m_spos[1], poly.m_verts[tri.m_indices[2]].m_spos[1]});
            float bbMaxX = std::max({poly.m_verts[tri.m_indices[0]].m_spos[0], poly.m_verts[tri.m_indices[1]].m_spos[0], poly.m_verts[tri.m_indices[2]].m_spos[0]});
            float bbMaxY = std::max({poly.m_verts[tri.m_indices[0]].m_spos[1], poly.m_verts[tri.m_indices[1]].m_spos[1], poly.m_verts[tri.m_indices[2]].m_spos[1]});

            // check if bounding box is at least partially on screen
            if (!((round(bbMaxX) < 0) || (round(bbMinX) > 511) || (round(bbMaxY) < 0) || (round(bbMinY) > 511))){

                // clamp y value
                if (bbMinY < 0) {
                    bbMinY = 0;
                }
                if (bbMaxY > 511) {
                    bbMaxY = 511;
                }

                for (float y = floor(bbMinY); y <= ceil(bbMaxY); y++) {

                    // check against triangle
                    std::vector<float>* xInts = new std::vector<float>;

                    Lineseg2D segment1 = Lineseg2D(v1.m_spos, v2.m_spos);
                    Lineseg2D segment2 = Lineseg2D(v1.m_spos, v3.m_spos);
                    Lineseg2D segment3 = Lineseg2D(v2.m_spos, v3.m_spos);

                    bool throwAway = segment1.xIntersect(y, xInts, bbMinX, bbMaxX);
                    throwAway = segment2.xIntersect(y, xInts, bbMinX, bbMaxX);
                    throwAway = segment3.xIntersect(y, xInts, bbMinX, bbMaxX);


                    if (xInts->size() > 1) {
                        float xMin = *std::min_element(xInts->begin(), xInts->end());
                        float xMax = *std::max_element(xInts->begin(), xInts->end());

                        // clamp x values
                        if (xMin < 0) {
                            xMin = 0;
                        }
                        if (xMax > 511){
                            xMax = 511;
                        }

                        for (float x = ceil(xMin); x <= xMax; x++) {

                            // find baryWeights
                            glm::vec3 ws = baryWeight(poly, tri, glm::vec3(x, y, 0));

                            // perspective correct divide
                            float zP = 1/(ws[0] + ws[1] + ws[2]);

                            if (zP <= zBuffer[int(round(x)) + 512*int(round(y))]) {
                                zBuffer[int(round(x)) + 512*int(round(y))] = zP;

                                // Interpolate UV
                                glm::vec2 uv = zP*(ws[0]*poly.m_verts[tri.m_indices[0]].m_uv + ws[1]*poly.m_verts[tri.m_indices[1]].m_uv + ws[2]*poly.m_verts[tri.m_indices[2]].m_uv);
                                glm::vec3 color = GetImageColor(uv, poly.mp_texture);

                                im.setPixelColor(int(round(x)), int(round(y)), qRgb(color.r, color.g, color.b));
                            }
                        }
                    }

                    delete xInts;
                }
            }
        }
    }
    return im;
}

glm::vec3 Rasterizer::baryWeight(const Polygon& poly, const Triangle& t, const glm::vec3 P) {
    glm::vec3 P1 = glm::vec3( poly.m_verts[t.m_indices[0]].m_spos[0], poly.m_verts[t.m_indices[0]].m_spos[1], 0);
    glm::vec3 P2 = glm::vec3( poly.m_verts[t.m_indices[1]].m_spos[0], poly.m_verts[t.m_indices[1]].m_spos[1], 0);
    glm::vec3 P3 = glm::vec3( poly.m_verts[t.m_indices[2]].m_spos[0], poly.m_verts[t.m_indices[2]].m_spos[1], 0);
    float S = 0.5 * lenVec3(glm::cross((P1-P2), (P3-P2)));
    float S1 = 0.5 * lenVec3(glm::cross((P-P2), (P3-P2)));
    float S2 = 0.5 * lenVec3(glm::cross((P-P3), (P1-P3)));
    float S3 = 0.5 * lenVec3(glm::cross((P-P1), (P2-P1)));
    float Z1 = poly.m_verts[t.m_indices[0]].m_spos[2];
    float Z2 = poly.m_verts[t.m_indices[1]].m_spos[2];
    float Z3 = poly.m_verts[t.m_indices[2]].m_spos[2];
    return(glm::vec3(S1/(Z1*S), S2/(Z2*S), S3/(Z3*S)));
}

void Rasterizer::ClearScene()
{
    m_polygons.clear();
}

float lenVec3(glm::vec3 v) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}
