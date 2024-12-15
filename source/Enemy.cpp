#include "../includes/Enemy.h"
#include <glm/gtc/type_ptr.hpp> // For glm::normalize

Enemy::Enemy(glm::vec3 startPosition, glm::vec3 defaultColor)
{
    enemyCube = new Cube(startPosition, 0.5f, defaultColor, Red); // Cube size 0.5f
    currentPosition = startPosition;
}

glm::vec3 Enemy::getPosition()
{
    return currentPosition;
}


Cube *Enemy::getEnemyCube()
{
    return enemyCube;
}

void Enemy::Move(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime) {

    std::vector<float> next_move_pixel = runAStar(newGridWidth, newGridHeight, playerPos.x, playerPos.z, currentPosition.x, currentPosition.z);
    if (next_move_pixel.empty()) {
        if (next_move_pixel.empty()) {
            std::cout << "next_move_pixel is empty. Stopping movement.\n";
        }
        return;
    }

    // Proceed with movement logic
    glm::vec3 targetNode{next_move_pixel[0], next_move_pixel[1], next_move_pixel[2]};
    glm::vec3 direction = glm::normalize(glm::vec3(targetNode.x, targetNode.y, targetNode.z) - currentPosition);
    float speed = 5.0f;
    currentPosition += direction * speed * deltaTime;

    std::min(15.f, currentPosition.x);
    std::min(15.f, currentPosition.y);
    std::min(15.f, currentPosition.z);
    std::max(5.f, currentPosition.x);
    std::max(5.f, currentPosition.y);
    std::max(5.f, currentPosition.z);

    // Update the enemy's position
    enemyCube->UpdateCube(enemyCube->getCubeSize(), currentPosition);
}