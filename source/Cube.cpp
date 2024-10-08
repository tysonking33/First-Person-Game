#include "../includes/Cube.h"

Cube::Cube(glm::vec3 newCubePosition, float newCubeSize) 
    : cubePosition(newCubePosition), cubeSize(newCubeSize) {
    // Allocate memory for cubeVector
    cubeVector = GenerateCube(cubeSize, cubePosition);
    cubeColor = Green;
    defaultColor = Green;
    hitColor = Red;

}

Cube::Cube(glm::vec3 newCubePosition, float newCubeSize, glm::vec3 newDefaultColor, glm::vec3 newHitColor) 
    : cubePosition(newCubePosition), cubeSize(newCubeSize) {
    // Allocate memory for cubeVector
    cubeVector = GenerateCube(cubeSize, cubePosition);
    cubeColor = newDefaultColor;
    defaultColor = newDefaultColor;
    hitColor = newHitColor;
}


std::vector<float> Cube::GenerateCube(float size, glm::vec3 position) {
    float halfSize = size / 2.0f;
    std::vector<float> vertices = {
        // Positions                      // Normals           // Texture Coords
        // Front face
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        // Back face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        // Left face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // Right face
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // Top face
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        // Bottom face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    };

    cubeVector = vertices;

    return vertices;
}

void Cube::UpdateCube(float size, glm::vec3 position) {
    //float halfSize = size / 2.0f;

    // Clear and update cubeVector based on new size and position
    cubeVector.clear();
    cubeVector = GenerateCube(size, position);

    // Update the internal position and size
    cubePosition = position;
    setCubePosition(position);
    cubeSize = size;
}

glm::vec3 Cube::getCubePosition(){
    return cubePosition;
}

void Cube::setCubePosition(glm::vec3 position) {
    cubePosition = position;
}

float Cube::getCubeSize(){
    return cubeSize;
}

void Cube::setCubeSize(float size) {
    cubeSize = size;
}

std::vector<float> Cube::getCubeVector(){
    return cubeVector;
}


void Cube::ChangeHitStatus(bool hit)
{
    cubeHitStatus = hit;
    if (cubeHitStatus)
    {
        cubeColor = hitColor;
    }
    else
    {
        cubeColor = defaultColor;
    }
}

glm::vec3 Cube::GetCubeColor()
{
    return cubeColor;
}

void Cube::setCubeColor(glm::vec3 newColor)
{
    cubeColor = newColor;
}
