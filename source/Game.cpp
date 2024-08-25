#include "../includes/Game.h"

Game::Game()
{
    player = new Player(glm::vec3(0.0f, 0.0f, 3.0f));
    // std::cout << "constructor\n";
    init();
    windowHeight = 600;
    windowWidth = 800;
    drawBullet = false;
    enemyGoLeft = true;
    enemySize = 1.f;
    drawBullet = true;
    enemyPosition = {0.f, 1.f, 3.f};
}

void Game::init()
{

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHeight = 600;

    // window = glfwCreateWindow(windowWidth, windowHeight, "3D FPS Game", nullptr, nullptr);
    window = glfwCreateWindow(800, 600, "3D FPS Game", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the Shader object here with the required parameters
    shader = new Shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    renderer = new Renderer();

    glEnable(GL_DEPTH_TEST);
}

// calculate mouse position
// current_angle = angle between mouse and center of screen
// where the camera rotates
// currentXMagnitude  = distance between mouse and center of screen, x component, for strength of horizontal rotation
// currentYMagnitude  = distance between mouse and center of screen, y component, for strength of vertical rotation
// speed of the magnitude rotation

void Game::calculateMouse()
{
    double centreXPos, centreYPos;
    double mouseXPos, mouseYPos;
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    centreXPos = windowWidth / 2;
    centreYPos = windowHeight / 2;

    float currentXMagnitude = mouseXPos - centreXPos;
    float currentYMagnitude = mouseYPos - centreYPos;

    float xOffset = mouseXPos - centreXPos;
    float yOffset = centreYPos - mouseYPos; // Reversed since y-coordinates go from bottom to top

    // Sensitivity control
    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    // Process the mouse movement
    player->processMouseMovement(xOffset, yOffset);

    glfwSetCursorPos(window, centreXPos, centreYPos);
}

void Game::processInput(float deltaTime)
{
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

    if ((glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) &&
        player->camera->getIsJumpingFlag() == false)
    {
        player->camera->zero_velocity();
    }

    if ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS))
    {
        exit(0);
    }

    // check later
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        player->playerSquat();
    }

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS))
    {
        // wall run left
        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && renderer->detectWallLeft(player->getCamera()) == true)
        {
            player->wallRunLeft(deltaTime);
        }

        // wall run right
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
        {
        }
    }

    // std::cout << "finished processKeyboardInput\n";

    /*-----------------------camera orientation movement-------------------------*/

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        player->processMouseMovement(-5, 0); // rotate left
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        player->processMouseMovement(5, 0); // rotate right
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        player->processMouseMovement(0, -5); // rotate down
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        player->processMouseMovement(0, 5); // rotate up

    /*-----------------------------Mouse click----------------------------------*/
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "Left mouse button clicked\n";
        renderer->DrawStreak(*shader, *player->camera);

        if (renderer->RayCast((player->getCamera()), renderer->convertPlainArrayToCubeFormat(enemyCube)) == true)
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

void Game::update(float deltaTime)
{
    processInput(deltaTime);
    player->camera->RunGravity();
    // calculateMouse();
    if (enemyGoLeft)
    {
        enemyPosition.x -= deltaTime;
        if (enemyPosition.x <= -10)
        {
            enemyGoLeft = false; // Corrected assignment
        }
    }
    else
    {
        enemyPosition.x += deltaTime;
        if (enemyPosition.x >= 10)
        {
            enemyGoLeft = true; // Corrected assignment
        }
    }
    renderer->UpdateCube(enemySize, enemyPosition, enemyCube);
    renderer->DrawCube(*shader, *player->camera, enemyCube);

}

void Game::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    renderer->DrawPlane(*shader, *player->camera);
    renderer->DrawWall(*shader, *player->camera);


    enemyCube = renderer->GenerateCube(enemySize, enemyPosition);
    renderer->DrawCube(*shader, *player->camera, enemyCube);

    glfwSwapBuffers(window);
}

void Game::run()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        update(deltaTime);
        render();

        glfwPollEvents();
    }

    glfwTerminate();
}
