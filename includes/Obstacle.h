#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"


class Obstacle
{
public:
    glm::vec3 position;
    float orientation;
    glm::vec3 dimensions;

public:
    Obstacle(glm::vec3 newPosition, float newOrientation, glm::vec3 newDimensions)
    {
        position = newPosition;
        orientation = newOrientation;
        dimensions = newDimensions;
    }

    // Function to get the 8 points of the cuboid
    std::vector<glm::vec3> getCuboidPoints()
    {
        std::vector<glm::vec3> points;
        glm::vec3 halfDims = dimensions * 0.5f;

        // Unrotated vertices in the local space
        std::vector<glm::vec3> localPoints = {
            {0, 0, 0}, // Bottom-left-front
            {dimensions.x, 0, 0},  // Bottom-right-front
            {dimensions.x, 0, dimensions.z},   // Bottom-right-back
            {0, 0, dimensions.z},  // Bottom-left-back
            {0, dimensions.y, 0},  // Top-left-front
            {dimensions.x, dimensions.y, 0},   // Top-right-front
            {dimensions.x, dimensions.y, dimensions.z},    // Top-right-back
            {0, dimensions.y, dimensions.z}    // Top-left-back
        };

        /*std::vector<glm::vec3> localPoints = {
            {-halfDims.x, -halfDims.y, -halfDims.z}, // Bottom-left-front
            {halfDims.x, -halfDims.y, -halfDims.z},  // Bottom-right-front
            {halfDims.x, -halfDims.y, halfDims.z},   // Bottom-right-back
            {-halfDims.x, -halfDims.y, halfDims.z},  // Bottom-left-back
            {-halfDims.x, halfDims.y, -halfDims.z},  // Top-left-front
            {halfDims.x, halfDims.y, -halfDims.z},   // Top-right-front
            {halfDims.x, halfDims.y, halfDims.z},    // Top-right-back
            {-halfDims.x, halfDims.y, halfDims.z}    // Top-left-back
        };*/


        // Rotation matrix (simple rotation around the Y axis for demonstration)
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(orientation), glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply rotation and translate to position
        for (const auto &point : localPoints)
        {
            glm::vec4 rotatedPoint = rotation * glm::vec4(point, 1.0f);
            points.push_back(glm::vec3(rotatedPoint) + position);
        }

        return points;
    }
};

#endif