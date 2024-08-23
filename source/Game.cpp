#include "../includes/Game.h"

Game::Game()  {
    player = new Player(glm::vec3(0.0f, 0.0f, 3.0f));
    //std::cout << "constructor\n";
    init();
    windowHeight = 600;
    windowWidth = 800;
    drawBullet = false;
}

void Game::init() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHeight = 600;


    //window = glfwCreateWindow(windowWidth, windowHeight, "3D FPS Game", nullptr, nullptr);
    window = glfwCreateWindow(800, 600, "3D FPS Game", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the Shader object here with the required parameters
    shader = new Shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    renderer = new Renderer();

    glEnable(GL_DEPTH_TEST);
}

//calculate mouse position
//current_angle = angle between mouse and center of screen
//where the camera rotates
//currentXMagnitude  = distance between mouse and center of screen, x component, for strength of horizontal rotation
//currentYMagnitude  = distance between mouse and center of screen, y component, for strength of vertical rotation
//speed of the magnitude rotation

/*void Game::calculateMouse()
{
    double centreXPos, centreYPos;
    double mouseXPos, mouseYPos;
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    centreXPos = windowWidth/2;
    centreYPos = windowHeight/2;

    float currentAngle = atan2(mouseYPos - centreYPos, mouseXPos - centreXPos);
    float currentXMagnitude = mouseXPos - centreXPos;
    float currentYMagnitude = mouseYPos - centreYPos;

    //find x rotation
    float xRotation = currentXMagnitude/windowWidth * 360; 
    //find y rotation
    float yRotation = currentYMagnitude/windowHeight * 360;
    player->processMouseMovement(xRotation, yRotation);

}*/


void Game::processInput(float deltaTime) {
    /*------------------------------camera position movement-----------------------------*/

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        player->processKeyboardInput(FORWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
        player->processKeyboardInput(BACKWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
        player->processKeyboardInput(LEFT, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
        player->processKeyboardInput(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->processKeyboardInput(JUMP, deltaTime);
    
    if ((glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS)&&
    player->camera->getIsJumpingFlag() == false)
    {
        player->camera->zero_velocity();
    }

    if ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS))
    {
        exit(0);
    }

    //check later
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        player->playerSquat();
    }

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS))
    {
        //wall run left
        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && renderer->detectWallLeft(player->getCamera()) == true)
        {
            player->wallRunLeft(deltaTime);
        }

        //wall run right
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
        {

        }
    }




    //std::cout << "finished processKeyboardInput\n";


    /*-----------------------camera orientation movement-------------------------*/
    //player->processMouseMovement(xpos, ypos);
    //player->processMouseScroll(ypos);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        player->processMouseMovement(-5, 0);        //rotate left
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        player->processMouseMovement(5, 0);        //rotate right
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        player->processMouseMovement(0, -5);         //rotate down
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        player->processMouseMovement(0, 5);         //rotate up

    /*-----------------------------Mouse click----------------------------------*/
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "Left mouse button clicked\n";
        drawBullet = true;


        float vertices[] = {
            // Top face
            // positions          // normals           // texture coords
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top-Left                   //a
            1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-Right                  //b
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right               //c
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right               //c
            -1.0f, 1.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-Left               //d
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top-Left                   //a

            // Bottom face
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Top-Left
            1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Top-Right
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right
            -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-Left
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Top-Left

            // Front face
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-Left
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // Top-Right
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom-Right
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom-Right
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom-Left
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-Left

            // Back face
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Top-Left
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // Top-Right
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // Bottom-Right
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // Bottom-Right
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // Bottom-Left
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Top-Left

            // Left face
            -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-Left
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-Right
            -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom-Right
            -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom-Right
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-Left
            -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-Left

            // Right face
            1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Top-Left
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top-Right
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-Right
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-Right
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-Left
            1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f   // Top-Left
        };

        if (renderer->RayCast((player->getCamera()), renderer->convertPlainArrayToCubeFormat(vertices)) == true)
        {
            bulletHit = true;
            renderer->ChangeHitStatus(bulletHit);
        }
        else
        {
            bulletHit = false;
            renderer->ChangeHitStatus(bulletHit);

        }
    }

    
}

void Game::update(float deltaTime) {
    processInput(deltaTime);
    player->camera->RunGravity();
    //calculateMouse();


}

void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    //renderer->DrawCube(*shader, player.camera);
    renderer->DrawPlane(*shader, *player->camera);
    renderer->DrawWall(*shader, *player->camera);

    //glm::vec3 start = player->camera->getPosition();
    //    glm::vec3 end = glm::vec3{start.x + 1, start.y + 1, start.z + 1};
    //        renderer->DrawCube(*shader, *player->camera, start, end);

    //if (drawBullet == true)
    {
        glm::vec3 position = player->camera->getPosition();
        renderer->DrawCube(*shader, *player->camera, position, 1);
    }

    glfwSwapBuffers(window);


}

void Game::run() {
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        update(deltaTime);
        render();

        glfwPollEvents();
    }

    glfwTerminate();
}
