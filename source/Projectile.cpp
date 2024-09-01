#include "../includes/Projectile.h"

void Update(float deltaTime){
        float velocityFactor  = MovementSpeed * deltaTime; // Calculate the velocity based on movement speed and delta time

}
void SetVelocity(glm::vec3 direction, float speed){
    velocity = 
}
// Other common projectile methods

void Update();        //Handles movement, updates the position based on velocity, and checks for collisions.
void OnCollision();   //Defines what happens when the projectile hits an object (e.g., apply damage, trigger explosion).
void Spawn();     //Initializes the projectile’s position, velocity, and other properties when it is fired.
void Destroy();   //Handles cleanup when the projectile’s lifespan ends or it collides with something.

Projectile::Projectile(glm::vec3 startPosition, glm::vec3 projectileVelocity){
    position = startPosition;
    velocity = projectileVelocity;
}