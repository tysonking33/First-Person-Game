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
    Position.y = 10.f;
}

// Returns the view matrix, which transforms world coordinates to the camera's view space
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up); // Calculate and return the view matrix
}

// Processes input for keyboard movement
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime; // Calculate the velocity based on movement speed and delta time

    // Update the camera's position based on the direction of movement
    if (direction == FORWARD)
        Position += Front * velocity;   // Move forward
    if (direction == BACKWARD)
        Position -= Front * velocity;   // Move backward
    if (direction == LEFT)
        Position -= Right * velocity;   // Move left
    if (direction == RIGHT)
        Position += Right * velocity;   // Move right

    // Print the current position of the camera (for debugging purposes)
    std::cout << "Current position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")\n"; 
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
        if (Pitch < -89.0f)
            Pitch = -89.0f;
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
}


void Camera::RunGravity()
{
    float gravity = 0.01f;
    if (Position.y > 3)
    {
        Position.y -= gravity;
    }
    else
    {
        Position.y = 3;
    }
    std::cout << "Current position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")\n"; 

}
