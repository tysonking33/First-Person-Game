#include <glm/glm.hpp>
#include <vector>
#include "Cube.h"
#include "AStar.h"

class Enemy {
private:
    Cube *enemyCube;
    glm::vec3 currentPosition;


public:
    Enemy(glm::vec3 startPosition, glm::vec3 defaultColor);
    glm::vec3 getPosition();
    Cube *getEnemyCube();
    void Move(int newGridWidth, int newGridHeight, glm::vec3 playerPos, float deltaTime);

};
