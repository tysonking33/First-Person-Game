#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

#include <array>
#include <vector>
#include "Color.h"
#include "Obstacle.h"
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

    void DrawCubeBasic(Shader &shader, Camera &camera, std::vector<float> vertices, glm::vec3 planeColor);

    std::vector<Vertex> convertPlainArrayToCubeFormat(std::vector<float> originalArray);

    void DrawWall(Shader &shader, Camera &camera);
    bool detectWallLeft(Camera *camera);
    void DrawCuboid(Shader &shader, Camera &camera, glm::vec3 position, float orientation, glm::vec3 dimensions);



    void DrawSquare(Shader &shader, glm::vec2 position, float size);
    void DrawCircle(Shader &shader, glm::vec2 position, float radius);
    void renderMinimap(Shader &shader, Camera &camera, glm::vec3 playerPosition, glm::vec3 enemyPosition, std::vector<Obstacle*> obstacles, float mapWidth, float mapHeight);


private:
    glm::vec3 planeColor; // Color variable
};
#endif
