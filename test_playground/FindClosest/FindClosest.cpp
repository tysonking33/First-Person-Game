#include <iostream>
#include <vector>

#define ArrayHeight = 20;
#define ArrayWidth = 20;
#define CubeSize = 2;


//returns a 2d vector of the coordinate that the player is in according to the vecmap
glm::vec2 findCoordinate(std::vector<std::vector<int>> vecmap, glm::vec3 playerPosition, float planeHeight, float planeWidth)
{
    glm::vec2 coordinate = glm::vec2(floor(playerPosition.x/planeHeight * cubeWidth), floor(playerPosition.y/planeHeight* cubeHeight));
}


int main()
{
    std::vector<std::vector<int>> vecmap(20, std::vector<int>(20, 0));


}