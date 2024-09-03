#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

#include <array>
#include <vector>
#include "Color.h"
struct Vertex
{
    std::array<float, 3> position;
    std::array<float, 3> normal;
    std::array<float, 2> texCoord;

    Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
        : position{x, y, z}, normal{nx, ny, nz}, texCoord{u, v}
    {
    }
};

class Renderer
{
public:
    Renderer() {}

    void DrawPlane(Shader &shader, Camera &camera);
    void setPlaneColor(const glm::vec3 &color); // Method to set the plane color

    void DrawStick(Shader &shader, Camera &camera, glm::vec3 start, glm::vec3 end);
    void DrawCubeEnemy(Shader &shader, Camera &camera, std::vector<float> vertices, glm::vec3 planeColor);
    void DrawCubeBasic(Shader &shader, Camera &camera, std::vector<float> vertices, glm::vec3 planeColor);

    void ChangeHitStatus(bool hit);
    bool RayCast(Camera *camera, std::vector<Vertex> DataPoints);
    std::vector<Vertex> convertPlainArrayToCubeFormat(std::vector<float> originalArray);
    bool CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates, glm::vec3 planeNormal);

    void DrawWall(Shader &shader, Camera &camera);
    bool detectWallLeft(Camera *camera);
void DrawStreak(Shader &shader, Camera &camera);
private:
    glm::vec3 planeColor; // Color variable
    bool cubeHitStatus;
};
#endif
