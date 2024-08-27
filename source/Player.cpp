#include "../includes/Player.h"

Player::Player(glm::vec3 startPosition){
    camera = new Camera(startPosition);
    //std::cout << "Player constructor\n";
    glm::vec3 newPosition = camera->getPosition() + camera->getFront();
    playerCube = new Cube(newPosition, 0.05f);
}

void Player::processKeyboardInput(Camera_Movement direction, float deltaTime)
{
    camera->ProcessKeyboard(direction, deltaTime);
    glm::vec3 newPosition = camera->getPosition() + camera->getFront();
    playerCube->UpdateCube(playerCube->getCubeSize(), newPosition);
}

void Player::processMouseMovement(float xoffset, float yoffset)
{
    camera->ProcessMouseMovement(xoffset, yoffset);
}

void Player::processMouseScroll(float yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

glm::mat4 Player::getViewMatrix()
{
    return camera->GetViewMatrix();
}

Camera *Player::getCamera()
{
    return camera;
}

void Player::playerSquat()
{
    camera->Squat();
}

void Player::wallRunLeft(float deltaTime)
{
    camera->wallRunLeft(deltaTime);
}