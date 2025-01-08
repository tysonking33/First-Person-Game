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
    //glm::vec3 playerPos = camera->getPosition() + camera->getFront();
    glm::vec3 playerPos = camera->getPosition();
    playerCube->UpdateCube(playerCube->getCubeSize(), playerPos);


    std::pair<int, int> playerCoordinates = std::make_pair(ceil(playerPos.x / (float)1), ceil(playerPos.z / (float)1));

    std::cout << "Player map position: " << playerCoordinates.first << ", " << playerCoordinates.second << std::endl;

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