#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Define the structure for a point (grid cell)
struct Point {
    int x, y;

    // Default constructor
    Point() : x(0), y(0) {}

    // Constructor with arguments
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

// Convert pixel coordinates to grid coordinates
Point getGridCoordinates(int x, int y, int cellWidth, int cellHeight);

// Heuristic function: Manhattan distance (for diagonal movement, we use Chebyshev distance)
int heuristic(const Point &a, const Point &b);

// A* Algorithm for pathfinding
vector<Point> astar(const Point &start, const Point &goal, const vector<vector<int>> &grid, int cellWidth, int cellHeight);

// Function to create the game map dynamically
vector<vector<int>> createGameMap(int width, int height, double obstacleProbability);

// Function to print the game map with symbols
void printGameMap(const vector<vector<int>> &gameMap, const Point &start, const Point &goal, const vector<Point> &path);

// Function to convert grid coordinates to pixel coordinates
Point getPixelCoordinates(const Point &gridPoint, int cellWidth, int cellHeight);

// Function to get the first step in both game map coordinates and pixel coordinates
std::vector<Point> getFirstStep(const vector<Point> &path, int cellWidth, int cellHeight);

// Function to run A* and return the first step in pixel coordinates
std::vector<float> runAStar(float newGridWidth, float newGridHeight, float playerX, float playerY, float enemyX, int enemyY);

#endif // ASTAR_H
