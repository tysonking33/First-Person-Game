#include "../includes/Projectile.h"

//find new position
void Projectile::Update(float deltaTime){
    glm::vec3 newPosition = projectileCube->getCubePosition() + velocity;
    projectileCube->UpdateCube(cubeSize, newPosition);
    age += deltaTime;
}

void Projectile::SetVelocity(glm::vec3 direction, float speed){
    velocity = speed * direction;
}


bool Projectile::isExpired(){
    return age >= lifespan;
}

Projectile::Projectile(glm::vec3 startPosition, glm::vec3 projectileVelocity, float deltaTime){
    startPosition.x += 0.02f;
    velocity = projectileVelocity;
    creationTime = deltaTime; 
    cubeSize = 0.1f;

    //cubeSize = 1.01f;
    projectileCube = new Cube(startPosition, cubeSize, Orange, Pink);
    lifespan = 20.f;
    age = 0.f;
}

Cube *Projectile::getCube()
{
    return projectileCube;
}

void Projectile::setColor(glm::vec3 newColor)
{
   projectileCube->setCubeColor(newColor);
}

glm::vec3 Projectile::getColor()
{
    return projectileCube->GetCubeColor();
}

void Projectile::projectileHit()
{
    projectileCube->ChangeHitStatus(true);
}