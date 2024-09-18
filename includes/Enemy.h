#ifndef ENEMY_H
#define ENEMY_H

#include "Camera.h"
#include "Cube.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp> // For length2 function




// Structure representing a coordinate
struct Coordinate {
    float x;            // X-coordinate
    float y;            // Y-coordinate
    float angleToNext;  // Angle to the next coordinate (in degrees)
};

class Enemy {
public:
    // Corrected constructor declarations
    Enemy(glm::vec3 startPosition);

    void Move(float deltaTime);

    glm::vec3 getPosition();
    void setRoute(std::vector<glm::vec3> newRoute, float deltaTime);
    Cube *getEnemyCube();

    // To be implemented later
    // void Shoot(float deltaTime);

private:
    Cube *enemyCube;
    int pathIndex;
    std::vector<Coordinate> pathCoords;

    std::vector<glm::vec3> CurrentRoute;
    glm::vec3 lastNodeTouched;
    glm::vec3 nextNode;
    glm::vec3 currentPosition;
    bool hitStatus;    
};

#endif
