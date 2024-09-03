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
    // Other common projectile methods

    void OnCollision();   //Defines what happens when the projectile hits an object (e.g., apply damage, trigger explosion).
    void Spawn();     //Initializes the projectile’s position, velocity, and other properties when it is fired.
    void Destroy();   //Handles cleanup when the projectile’s lifespan ends or it collides with something.

    Projectile(glm::vec3 startPosition, glm::vec3 projectileVelocity, float deltaTime);
        Cube *getCube();

    void setColor(glm::vec3 newColor);
    glm::vec3 getColor();
    bool isExpired();



protected:
    glm::vec3 position;
    glm::vec3 velocity;
    float damage;
    float lifespan;
    float creationTime;
    float cubeSize;
    glm::vec3 color;
    float age;
    // Other attributes
};



#endif