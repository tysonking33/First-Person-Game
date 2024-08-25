#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <math.h>

class Projectile {
public:
    virtual void Update(float deltaTime);
    void SetVelocity(glm::vec3 direction, float speed);
    // Other common projectile methods

    void Update();        //Handles movement, updates the position based on velocity, and checks for collisions.
    void OnCollision();   //Defines what happens when the projectile hits an object (e.g., apply damage, trigger explosion).
    void Spawn();     //Initializes the projectile’s position, velocity, and other properties when it is fired.
    void Destroy();   //Handles cleanup when the projectile’s lifespan ends or it collides with something.
protected:
    glm::vec3 position;
    glm::vec3 velocity;
    float damage;
    float lifespan;
    // Other attributes
};



#endif