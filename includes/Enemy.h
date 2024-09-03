#ifndef ENEMY_H
#define ENEMY_H

#include "Camera.h"
#include "Cube.h"
#include <iostream>

/* get rid of when integrating the AStar.h header */
// Structure representing a coordinate
struct Coordinate
{
    float x;               // X-coordinate
    float y;               // Y-coordinate
    float angleToNext;     // Angle to the next coordinate (in degrees)
};

class Enemy {
    Cube *enemyCube;

    int pathIndex;

    std::vector<Coordinate> pathCoords;

    Enemy(glm::vec3 startPosition);

    void Move(float deltaTime);

    // do later
    void Shoot(float deltaTime);
};

#endif