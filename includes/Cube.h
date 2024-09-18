#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Color.h"
#include <array>
#include <vector>


class Cube
{
public:
    std::vector<float> GenerateCube(float size, glm::vec3 position);
    void UpdateCube(float size, glm::vec3 position);

    std::vector<float> getCubeVector();

    Cube(glm::vec3 newCubePosition, float newCubeSize);
    Cube(glm::vec3 newCubePosition, float newCubeSize, glm::vec3 newDefaultColor, glm::vec3 newHitColor);

    
    void setCubePosition(glm::vec3 position);
    void setCubeColor(glm::vec3 newColor);

    float getCubeSize();

    void setCubeSize(float size);
    glm::vec3 getCubePosition();
    void ChangeHitStatus(bool hit);
    glm::vec3 GetCubeColor();


private:
    std::vector<float> cubeVector;
    glm::vec3 cubePosition;
    float cubeSize;
    bool cubeHitStatus;
    glm::vec3 cubeColor;
    glm::vec3 defaultColor;
    glm::vec3 hitColor;
};

#endif