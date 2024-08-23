#include "../includes/Camera.h" // Include the Camera class header file

// Constructor for the Camera class
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    // Initialize member variables using an initializer list
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), // Set the initial front direction to face forward (negative Z-axis)
      MovementSpeed(SPEED),                // Initialize movement speed with a predefined value
      MouseSensitivity(SENSITIVITY),       // Initialize mouse sensitivity with a predefined value
      Zoom(ZOOM)                           // Initialize zoom level with a predefined value
{
    Position = position; // Set the camera's initial position
    WorldUp = up;        // Set the world's up direction (usually the positive Y-axis)
    Yaw = yaw;           // Set the camera's initial yaw (rotation around the Y-axis)
    Pitch = pitch;       // Set the camera's initial pitch (rotation around the X-axis)
    updateCameraVectors(); // Update the camera's direction vectors based on the yaw and pitch
    Position.y = 3.f;
    isJumping = false;
    GRAVITY = 10.0f;
    Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Returns the view matrix, which transforms world coordinates to the camera's view space
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up); // Calculate and return the view matrix
}

// Processes input for keyboard movement
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocityFactor  = MovementSpeed * deltaTime; // Calculate the velocity based on movement speed and delta time
    float JUMP_STRENGTH = 10.f;
    float movement_friction = 3.f;

    if (isJumping == false)
    {
        Velocity.y = 0.0f;
    }
    if (isJumping) {
        Velocity.y -= GRAVITY * deltaTime; // Apply gravity
        Position += Velocity * deltaTime;   // Update position based on velocity

        if (Position.y <= 1.0f) {
            Position.y = 1.0f; // Reset position to ground level
            Velocity.y = 0.0f; // Reset vertical velocity
            isJumping = false; // Stop jumping
        }
    }
    

    // Update the camera's position based on the direction of movement
    if (direction == FORWARD){
        std::cout << "move forward\n";
        Velocity += Front * velocityFactor ;   // Move forward
    }
    if (direction == BACKWARD){
        std::cout << "move backwards\n";
        Velocity -= Front * velocityFactor ;   // Move backward
    }
    if (direction == LEFT){
        std::cout << "move left\n";
        Velocity -= Right * velocityFactor ;   // Move left
    }
    if (direction == RIGHT){
        std::cout << "move right\n";
        Velocity += Right * velocityFactor ;   // Move right
    }
    if (direction == JUMP && isJumping == false)
    {
        Velocity.y = JUMP_STRENGTH; // Set initial jump velocity
        isJumping = true; // Set jumping state
    }

    
    Velocity.x -= Velocity.x * movement_friction * deltaTime;
    Velocity.z -= Velocity.z * movement_friction * deltaTime;
    Position += Velocity * deltaTime;



    // Print the current position of the camera (for debugging purposes)
    std::cout << "Current position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")\n";
    std::cout << "Current velocity: ("  << Velocity.x << ", " << Velocity.y << ", " << Velocity.z << ")\n";
    previousPosition = Position;
}

// Processes input from mouse movement to control the camera's orientation
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity; // Scale the xoffset by mouse sensitivity
    yoffset *= MouseSensitivity; // Scale the yoffset by mouse sensitivity

    Yaw   += xoffset; // Update the yaw based on the xoffset
    Pitch += yoffset; // Update the pitch based on the yoffset

    // Constrain the pitch to avoid extreme up or down views
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -270.0f)
            Pitch = -270.0f;
    }

    updateCameraVectors(); // Update the camera's direction vectors based on the new yaw and pitch
}

// Processes input from the mouse scroll wheel to adjust the camera's zoom
void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset; // Decrease zoom based on scroll wheel input

    // Constrain the zoom level to be within a certain range
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f; 
}

// Updates the camera's direction vectors based on the current yaw and pitch
void Camera::updateCameraVectors() {
    glm::vec3 front;
    // Calculate the new front vector based on yaw and pitch using trigonometric functions
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front); // Normalize the front vector to ensure it has a unit length

    // Recalculate the right and up vectors
    Right = glm::normalize(glm::cross(Front, WorldUp)); // Right vector is perpendicular to the front and world up vectors
    Up    = glm::normalize(glm::cross(Right, Front));   // Up vector is perpendicular to the right and front vectors

std::cout << "Current front:" << glm::to_string(front)<<std::endl;
}


void Camera::RunGravity()
{
    float gravity = 0.05f;
    if (Position.y > 1)
    {
        Position.y -= gravity;
    }
    else
    {
        Position.y = 1;
        isJumping= false;
    }
    //std::cout << "Current position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")\n";
    previousPosition =  Position;

}


void Camera::zero_velocity()
{
    Velocity = {0,0,0};
}

bool Camera::getIsJumpingFlag()
{
    return isJumping;
}

glm::vec3 Camera::getPosition()
{
    return Position;
}

glm::vec3 Camera::getFront()
{
    return Front;
}


float Camera::getYaw()
{
    return Yaw;
}