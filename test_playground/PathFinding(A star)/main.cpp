#include "AStar.h"

int main() {
    /*std::vector<std::vector<int>> map = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };*/

    std::vector<std::vector<int>> map = {
        {10, 11, 12, 13, 14},
        {15, 16, 17, 1, 18},
        {1, 1, 19, 1, 20},
        {21, 22, 23, 1, 24},
        {25, 1, 26, 1, 27},
        {28, 1, 29, 30, 31},
        {32, 1, 33, 1, 34},
        {35, 36, 37, 38, 39}
    };


    Cell start;
    start.g = 0;
    start.h = 0;
    start.f = 0;
    start.parent = nullptr;
    start.x = 0;
    start.y = 0;
    start.value = 10;

    Cell end;
    end.g = 0;
    end.h = 0;
    end.f = 0;
    end.x = 7;
    end.y = 0;


    std::cout << map[7][0] << "\n";

    AStar aSearchObj(600, 300, (float)map.size(), (float)map[0].size());
    aSearchObj.AStarSearchBasic(map, start, end);

    aSearchObj.printPath();

    aSearchObj.translateIdxToCoords();
    
    
    return 0;
}
