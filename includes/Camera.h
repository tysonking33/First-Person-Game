#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  15.f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {
public:
    glm::vec3 previousPosition;
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float Yaw;
    float Pitch;
    
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    bool isJumping;
    bool isWallRunLeft;
    float GRAVITY;
    glm::vec3 Velocity;

    Camera(glm::vec3 position = glm::vec3(0.0f, 10.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void RunGravity();
    void zero_velocity();

    bool getIsJumpingFlag();
    glm::vec3 getPosition();
    glm::vec3 getFront();
    float getYaw();
    void Squat();
    void wallRunLeft(float deltaTime);




private:
    void updateCameraVectors();
};

#endif
