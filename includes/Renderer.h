#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

#include <array>
#include <vector>

const glm::vec3 Red = glm::vec3(1.0f, 0.0f, 0.0f);          // Pure Red
const glm::vec3 Green = glm::vec3(0.0f, 1.0f, 0.0f);        // Pure Green
const glm::vec3 Blue = glm::vec3(0.0f, 0.0f, 1.0f);         // Pure Blue
const glm::vec3 White = glm::vec3(1.0f, 1.0f, 1.0f);        // Pure White
const glm::vec3 Black = glm::vec3(0.0f, 0.0f, 0.0f);        // Pure Black
const glm::vec3 Yellow = glm::vec3(1.0f, 1.0f, 0.0f);       // Pure Yellow
const glm::vec3 Cyan = glm::vec3(0.0f, 1.0f, 1.0f);         // Cyan (Aqua)
const glm::vec3 Magenta = glm::vec3(1.0f, 0.0f, 1.0f);      // Magenta (Fuchsia)
const glm::vec3 Orange = glm::vec3(1.0f, 0.5f, 0.0f);       // Orange
const glm::vec3 Purple = glm::vec3(0.5f, 0.0f, 0.5f);       // Purple
const glm::vec3 Pink = glm::vec3(1.0f, 0.75f, 0.8f);        // Pink
const glm::vec3 Gray = glm::vec3(0.5f, 0.5f, 0.5f);         // Medium Gray
const glm::vec3 LightGray = glm::vec3(0.75f, 0.75f, 0.75f); // Light Gray
const glm::vec3 DarkGray = glm::vec3(0.25f, 0.25f, 0.25f);  // Dark Gray
const glm::vec3 Brown = glm::vec3(0.6f, 0.3f, 0.0f);        // Brown
const glm::vec3 Gold = glm::vec3(1.0f, 0.84f, 0.0f);        // Gold

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
std::vector<float> GenerateCube(float size, const glm::vec3& position);
    void DrawCube(Shader &shader, Camera &camera, std::vector<float> vertices);
    void ChangeHitStatus(bool hit);
    bool RayCast(Camera *camera, std::vector<Vertex> DataPoints);
std::vector<Vertex> convertPlainArrayToCubeFormat(std::vector<float> originalArray);
    bool CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates, glm::vec3 planeNormal);

    void DrawWall(Shader &shader, Camera &camera);
    bool detectWallLeft(Camera *camera);
private:
    glm::vec3 planeColor; // Color variable
    bool cubeHitStatus;
};
#endif
