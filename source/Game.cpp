#include "../includes/Game.h"

Game::Game()
{
    // generate 2d array for the map 1.f by 1.f, with player positoon and enemy position
    // inside vector
    vecmap = std::vector(20, std::vector<int>(20, 0));
    player = new Player(glm::vec3(3.0f, 3.0f, 3.0f));
    init();
    windowHeight = 600;
    windowWidth = 800;
    mapWidth = 20;
    mapHeight = 20;


    crosshairPosition = player->camera->getPosition() + 0.1f * player->camera->getFront();
    crosshairCube = new Cube(crosshairPosition, 0.001f);
    crosshairSize = 0.001f;
    float FLOAT_MAX = 10;
    float FLOAT_MIN = -10;
    enemy = new Enemy(glm::vec3{20.f, 3.f, 20.f}, Brown);
    physics = new Physics_Engine();
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

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    renderer->DrawPlane(*shader, *player->camera);
    renderer->DrawWall(*shader, *player->camera);

    for (auto projectile : projectiles)
    {
        renderer->DrawCubeBasic(*shader, *player->camera, projectile->getCube()->getCubeVector(), projectile->getCube()->GetCubeColor());
    }

    crosshairPosition = player->camera->getPosition() + 0.1f * player->camera->getFront();
    crosshairCube->UpdateCube(crosshairSize, crosshairPosition);
    renderer->DrawCubeBasic(*shader, *player->camera, crosshairCube->getCubeVector(), White);
    renderer->DrawCubeBasic(*shader, *player->camera, enemy->getEnemyCube()->getCubeVector(), Brown);

    glfwSwapBuffers(window);
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
    if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
        exit(1);
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

    if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS))
    {
        std::cout << "Exiting program\n";
        exit(0);
    }

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

        glm::vec3 startPosition = player->getCamera()->getPosition();
        glm::vec3 direction = player->getCamera()->getFront();

        // Create the projectile and add it to the vector
        Projectile *newProjectile = new Projectile(startPosition, direction, deltaTime);
        projectiles.push_back(newProjectile);

        /*
        if (physics->RayCast((player->getCamera()), renderer->convertPlainArrayToCubeFormat(enemy->getEnemyCube()->getCubeVector())) == true)
        {
            bulletHit = true;
            enemy->getEnemyCube()->ChangeHitStatus(bulletHit);
        }
        else
        {
            bulletHit = false;
            enemy->getEnemyCube()->ChangeHitStatus(bulletHit);
        }
        */
    }
}

void Game::update(float deltaTime)
{
    processInput(deltaTime);
    player->camera->RunGravity();

    glm::vec3 playerPos = player->playerCube->getCubePosition();
    playerPos.z -= playerPos.z;

    glm::vec3 p2{3,3,3}; 

    enemy->Move(mapWidth, mapHeight, p2, deltaTime);

    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        (*it)->Update(deltaTime);
        if (physics->cubeCollision(enemy->getEnemyCube(), (*it)->getCube()) == true)
        {
            (*it)->projectileHit();
            delete *it;
            it = projectiles.erase(it);
        }
        else if ((*it)->isExpired())
        {
            delete *it;
            it = projectiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
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
