#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <array>
#include <vector>

class Cube
{
public:
    std::vector<float> GenerateCube(float size, glm::vec3 position);
    void UpdateCube(float size, glm::vec3 position);

    std::vector<float> getCubeVector();

    Cube(glm::vec3 newCubePosition, float newCubeSize);

    
    void setCubePosition(glm::vec3 position);

    float getCubeSize();

    void setCubeSize(float size);

private:
    std::vector<float> cubeVector;
    glm::vec3 cubePosition;
    float cubeSize;

    glm::vec3 getCubePosition();

};

#endif