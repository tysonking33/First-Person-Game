#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <math.h>
#include <set>
#include <queue>

struct Cell
{
    float g; // movement cost from starting point to a given square ont he grid, follwing the current path generated
    float h; // estimate movement cost from given squat to final destination
    float f; // sum of g and h
    struct Cell *parent;
    float x;
    float y;
    float value;

    // Add the equality operator to compare Cell objects
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y && g == other.g &&
               h == other.h && f == other.f && parent == other.parent;
    }
    
};

class AStar
{
public:
    void AStarSearchBasic(std::vector<std::vector<int>> &map, Cell start, Cell end);

    void printPath();

    

    std::vector<Cell> finalPath;
};

#endif