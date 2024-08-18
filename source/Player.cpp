#include "../includes/Player.h"

Player::Player(glm::vec3 startPosition){
    camera = new Camera(startPosition);
    std::cout << "Player constructor\n";
}

void Player::processKeyboardInput(Camera_Movement direction, float deltaTime)
{
    camera->ProcessKeyboard(direction, deltaTime);
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