#ifndef GAME_H
#define GAME_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Player.h"
#include "Renderer.h"

class Game {
public:
    Game();
    void run();

private:
    void init();
    void processInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void calculateMouse();
    float windowHeight, windowWidth;

    GLFWwindow* window;
    Shader *shader;  // Declaration only
    Player *player;
    Renderer *renderer;

    bool drawBullet;
    bool bulletHit;
    glm::vec3 enemyPosition;
    bool enemyGoLeft;
    float enemySize;


    Cube *enemyCube;
};

#endif