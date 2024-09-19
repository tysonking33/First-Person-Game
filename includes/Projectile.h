#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include "Cube.h"
#include "Color.h"


class Projectile {
public:
    Cube *projectileCube;
    void Update(float deltaTime);
    void SetVelocity(glm::vec3 direction, float speed);


    Projectile(glm::vec3 startPosition, glm::vec3 projectileVelocity, float deltaTime);
    Cube *getCube();

    void setColor(glm::vec3 newColor);
    glm::vec3 getColor();
    bool isExpired();
    void projectileHit();



protected:
    glm::vec3 velocity;
    float damage;
    float lifespan;
    float creationTime;
    float cubeSize;
    float age;
    // Other attributes
};



#endif