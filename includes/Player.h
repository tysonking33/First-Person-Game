#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Cube.h"
#include <iostream>

class Player {
public:
    Camera *camera;

    Cube *playerCube;

    Player(glm::vec3 startPosition);

    void processKeyboardInput(Camera_Movement direction, float deltaTime);

    void processMouseMovement(float xoffset, float yoffset);

    void processMouseScroll(float yoffset);

    glm::mat4 getViewMatrix();
    Camera *getCamera();
    void playerSquat();
    void wallRunLeft(float deltaTime);

};

#endif