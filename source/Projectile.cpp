#include "../includes/Projectile.h"

//find new position
void Projectile::Update(float deltaTime){
    glm::vec3 newPosition = position + deltaTime * velocity;
    projectileCube->UpdateCube(cubeSize, newPosition);
    position = newPosition;
        age += deltaTime;

}

void Projectile::SetVelocity(glm::vec3 direction, float speed){
    velocity = speed * direction;
}
// Other common projectile methods

/*
void OnCollision();   //Defines what happens when the projectile hits an object (e.g., apply damage, trigger explosion).
void Spawn();     //Initializes the projectile’s position, velocity, and other properties when it is fired.
void Destroy();   //Handles cleanup when the projectile’s lifespan ends or it collides with something.
*/


bool Projectile::isExpired(){
    return age >= lifespan;
}

Projectile::Projectile(glm::vec3 startPosition, glm::vec3 projectileVelocity, float deltaTime){
    startPosition.x += 0.02f;
    position = startPosition;
    velocity = projectileVelocity;
    creationTime = deltaTime; 
    cubeSize = 0.01f;
    projectileCube = new Cube(position, cubeSize);
    color = Magenta;
    lifespan = 1.f;
    age = 0.f;
}

Cube *Projectile::getCube()
{
    return projectileCube;
}

void Projectile::setColor(glm::vec3 newColor)
{
    color = newColor;
}
glm::vec3 Projectile::getColor()
{
    return color;
}