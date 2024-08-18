#include "../includes/Game.h"

Game::Game()  {
    player = new Player(glm::vec3(0.0f, 0.0f, 3.0f));
    std::cout << "constructor\n";
    init();
}

void Game::init() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(800, 600, "3D FPS Game", nullptr, nullptr);
    if (!window) {
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

void Game::processInput(float deltaTime) {
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
        player->processKeyboardInput(FORWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
        player->processKeyboardInput(BACKWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
        player->processKeyboardInput(LEFT, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
        player->processKeyboardInput(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->processKeyboardInput(JUMP, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS)&&
    (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS)&&
    player->camera->getIsJumpingFlag() == false)
    {
        player->camera->zero_velocity();
    }
    

    /*if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        player->processKeyboardInput(FORWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
        player->processKeyboardInput(BACKWARD, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
        player->processKeyboardInput(LEFT, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
        player->processKeyboardInput(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->processKeyboardInput(JUMP, deltaTime);
        */


    //std::cout << "finished processKeyboardInput\n";

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    //player.camera.rotateCamera(xpos, ypos);
    player->processMouseMovement(xpos, ypos);
    player->processMouseScroll(ypos);
}

void Game::update(float deltaTime) {
    processInput(deltaTime);
    player->camera->RunGravity();

}

void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    //renderer->DrawCube(*shader, player.camera);
    renderer->DrawPlane(*shader, *player->camera);

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
