#include "../includes/Enemy.h"

Enemy::Enemy(glm::vec3 startPosition) {
    // Initialize the enemy's cube with the start position and size
    enemyCube = new Cube(startPosition, 0.5f); // Assuming size 0.5f for the cube
    currentPosition = startPosition;


    // Initialize the current route (this should be a vector of glm::vec3)
    CurrentRoute = {
        glm::vec3(30, 37.5f, 0),
        glm::vec3(90, 112.5f, 0),
        glm::vec3(150, 187.5f, 0),
        glm::vec3(210, 112.5f, 0),
        glm::vec3(270, 37.5f, 0),
        glm::vec3(330, 37.5f, 0),
        glm::vec3(390, 37.5f, 0),
        glm::vec3(450, 37.5f, 0)
    };

    // Set initial nodes if necessary, ensuring they are within bounds
    if (!CurrentRoute.empty()) {
        lastNodeTouched = CurrentRoute[0]; // Start with the first node as the last touched
        if (CurrentRoute.size() > 1) {
            nextNode = CurrentRoute[1]; // Set the next node if available
        }
    }

    // Initialize the path index to start moving from the first node
    pathIndex = 0;
    hitStatus = false;
}

void Enemy::Move(float deltaTime)
{
    //find normalised direction vector
    glm::vec3 direction = nextNode - currentPosition;
    direction = glm::normalize(direction);

    //check proximity to node, if so, update
    float distanceSquared = glm::length2(direction); // using euclidean distance

    float offset = 0.1f;
    if (distanceSquared <= offset * offset)
    {
        //go to next distance
        pathIndex++;
        if (pathIndex < (int)CurrentRoute.size())
        {
            lastNodeTouched = CurrentRoute[pathIndex];
            nextNode = CurrentRoute[pathIndex];
        }
    }

    float speed = 0.2f;

    //update position
    currentPosition = currentPosition + direction * speed * deltaTime;

    enemyCube->UpdateCube(enemyCube->getCubeSize(), currentPosition);
}


glm::vec3 Enemy::getPosition()
{
    return currentPosition;
}

void Enemy::setRoute(std::vector<glm::vec3> newRoute, float deltaTime)
{
    CurrentRoute = newRoute;
     // Set initial nodes if necessary, ensuring they are within bounds
    if (!CurrentRoute.empty()) {
        lastNodeTouched = CurrentRoute[0]; // Start with the first node as the last touched
        if (CurrentRoute.size() > 1) {
            nextNode = CurrentRoute[1]; // Set the next node if available
        }
    }

    // Initialize the path index to start moving from the first node
    pathIndex = 0;
    hitStatus = false;
    Move(deltaTime);
}

Cube *Enemy::getEnemyCube()
{
    return enemyCube;
}
