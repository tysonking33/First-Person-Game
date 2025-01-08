#include <glm/glm.hpp>
#include <vector>
#include "Cube.h"
#include "AStar.h"
#include "Obstacle.h"

class Enemy {
private:
    Cube *enemyCube;
    glm::vec3 currentPosition;
    glm::vec3 targetNode;
    AStar *astar_obj;
    std::pair<int, int> previousMapPosition;



public:
    Enemy(glm::vec3 startPosition, glm::vec3 defaultColor, int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector);    
    glm::vec3 getPosition();
    Cube *getEnemyCube();
    void Move(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector);
    bool hasReachedTarget();
    std::vector<float> get_next_pixel(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector);
    void generate_new_enemy_AStar_path(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime, std::vector<Obstacle *> obstacleVector);
    AStar *getAStar();
};
