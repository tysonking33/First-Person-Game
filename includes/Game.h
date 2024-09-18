#ifndef GAME_H
#define GAME_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Player.h"
#include "Renderer.h"
#include "Projectile.h"
#include "Physics_Engine.h"

#include<functional>

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
    Physics_Engine *physics;

    bool drawBullet;
    bool bulletHit;
    glm::vec3 enemyPosition;
    bool enemyGoLeft;
    float enemySize;


    Cube *enemyCube;
    glm::vec3 crosshairPosition;
    Cube *crosshairCube;
    float crosshairSize;
    //Enemy *enemy;
    std::vector<Projectile*> projectiles; // Store multiple projectiles


   
    template<typename Func, typename T1, typename T2, typename ...Args>
    bool DoThingForTimeSec(Func func, float seconds, float startTime, Args... args);


    glm::vec2 findCoordinate(std::vector<std::vector<int>> vecmap, glm::vec3 playerPosition, float planeHeight, float planeWidth, float cubeDimensions);
};

#endif