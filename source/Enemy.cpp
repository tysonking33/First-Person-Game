#include "../includes/Enemy.h"
#include <glm/gtc/type_ptr.hpp> // For glm::normalize

Enemy::Enemy(glm::vec3 startPosition, glm::vec3 defaultColor, int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector)
{
    enemyCube = new Cube(startPosition, 0.5f, defaultColor, Red); // Cube size 0.5f
    currentPosition = startPosition;
    targetNode = startPosition; // Initial target is the starting position
    astar_obj = new AStar(newGridWidth, newGridHeight, playerPos.x, playerPos.z, currentPosition.x, currentPosition.z, obstacleVector);

    std::vector<float> next_move_pixel = astar_obj->getNextNode();
    if (next_move_pixel.size() < 2)
    {
        std::cerr << "Error: AStar pathfinding did not return valid coordinates!" << std::endl;
        // Handle the error appropriately, e.g., set a default target position
        targetNode = currentPosition; // Or some fallback logic
    }
    else
    {
        targetNode = glm::vec3(next_move_pixel[0], 0, next_move_pixel[1]);
    }

    previousMapPosition = std::make_pair(-1,-1);
}

glm::vec3 Enemy::getPosition()
{
    return currentPosition;
}

Cube *Enemy::getEnemyCube()
{
    return enemyCube;
}

// Helper function to check if the enemy has reached the target node
bool Enemy::hasReachedTarget()
{
    float current_distance = glm::length(currentPosition - targetNode);
    ///std::cout << "current_distance: " << current_distance << std::endl;
    return current_distance <= 1.f; // Threshold for reaching the target
}

void Enemy::generate_new_enemy_AStar_path(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector)
{
    astar_obj->reset_AStar(newGridWidth, newGridHeight, playerPos.x, playerPos.z, currentPosition.x, currentPosition.z, obstacleVector);

    std::vector<float> next_move_pixel = astar_obj->getNextNode();

    float move_speed = 4.0f;

    if (next_move_pixel.empty())
    {
        std::cout << "No valid path found. Moving towards the player directly." << std::endl;
        // Move directly towards the player if no path is found
        glm::vec3 direction = glm::normalize(playerPos - currentPosition);
        currentPosition += direction * move_speed * deltaTime;
    }
    else
    {
        //std::cout << "updating target node++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        // Update the target node if A* gives a valid move
        targetNode = glm::vec3(next_move_pixel[1], 0, next_move_pixel[0]);

        // Move towards the target node
        glm::vec3 direction = glm::normalize(targetNode - currentPosition);
        currentPosition += direction * move_speed * deltaTime;
    }

    // Clamping the position within boundaries
    currentPosition.x = std::clamp(currentPosition.x, 1.f, 19.f);
    currentPosition.y = std::clamp(currentPosition.y, 1.f, 19.f);
    currentPosition.z = std::clamp(currentPosition.z, 1.f, 19.f);

    // Update the enemy's cube position
    enemyCube->UpdateCube(enemyCube->getCubeSize(), currentPosition);

}

void Enemy::Move(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector)
{
    float move_speed = 4.f;

    if (glm::length(currentPosition - playerPos) <= 1.f)
    {
        std::cout << "enemy reached target. stoping movement\n";
        return;
    }
    else
    {
        // Check if the enemy has reached the next node, get the next node
        if (hasReachedTarget())
        {
            // Run A* again to get the next move
            std::vector<float> next_move_pixel = astar_obj->getNextNode();

            if (next_move_pixel.empty())
            {
                std::cout << "No valid path found. Moving towards the player directly." << std::endl;
                // Move directly towards the player if no path is found
                glm::vec3 direction = glm::normalize(playerPos - currentPosition);
                currentPosition += direction * move_speed * deltaTime;
            }
            else
            {
                // Update the target node, to the next node in the path if A* gives a valid move
                targetNode = glm::vec3(next_move_pixel[1], 0, next_move_pixel[0]);

                // Move towards the target node
                glm::vec3 direction = glm::normalize(targetNode - currentPosition);
                currentPosition += direction * move_speed * deltaTime;
            }
        }
        else
        {
            //std::cout << "moving to current target node\n";
            // If not reached the target node, move towards it
            glm::vec3 direction = glm::normalize(targetNode - currentPosition);

            currentPosition += direction * move_speed * deltaTime;
        }

        // Clamping the position within boundaries
        currentPosition.x = std::clamp(currentPosition.x, 1.f, 19.f);
        currentPosition.y = std::clamp(currentPosition.y, 1.f, 19.f);
        currentPosition.z = std::clamp(currentPosition.z, 1.f, 19.f);

        std::pair<int, int> enemyCoordinatePos = astar_obj->getGridCoordinates(currentPosition.x, currentPosition.z, 1, 1);

        // Only print the new position if it has changed
        if (enemyCoordinatePos != previousMapPosition)
        {
            std::cout << "Enemy map position: " << enemyCoordinatePos.first << ", " << enemyCoordinatePos.second << std::endl;
            previousMapPosition = enemyCoordinatePos; // Update the previous position
        }

        astar_obj->printMapUtil(playerPos.x, playerPos.z, currentPosition.x, currentPosition.z, obstacleVector);

        // Update the enemy's cube position
        enemyCube->UpdateCube(enemyCube->getCubeSize(), currentPosition);
    }
}

AStar *Enemy::getAStar()
{
    return  astar_obj;
}