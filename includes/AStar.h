#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <utility> // For std::pair
#include "Obstacle.h"

// Node structure to represent a grid node
struct Node {
    int x, y;     // Position of the node
    int g, h;     // g is the cost to reach the node, h is the heuristic (estimated cost to goal)
    Node *parent; // Pointer to the parent node

    // Constructor
    Node(int x, int y, int g = 0, int h = 0, Node *parent = nullptr);

    // f = g + h, used to sort nodes in the priority queue
    int f() const;

    bool operator>(const Node &other) const;
};

// Directions for movement: 8 directions (up, down, left, right, and 4 diagonals)
extern const std::vector<std::pair<int, int>> directions;

class AStar{
    private:
        std::vector<Node *> path;
        float playfieldWidth;
        float playfieldHeight;
        int current_node;
        int cellWidth;
        int cellHeight;
        int gridWidth;
        int gridHeight;

    public:
        AStar(float newPlayfieldWidth, float newPlayfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector);

        // Check if a position is within bounds and not an obstacle
        bool isValid(int x, int y, int rows, int cols, const std::vector<std::vector<int>> &grid);

        // Heuristic function: Chebyshev distance (max of horizontal and vertical distance)
        int heuristic(int x1, int y1, int x2, int y2);

        // A* algorithm to find the shortest path
        std::vector<Node *> aStar(const std::vector<std::vector<int>> &grid, Node *start, Node *goal);

        // Function to print the grid with the path marked
        void printMapWithPath(const std::vector<std::vector<int>> &grid, const std::vector<Node *> &path, Node *start, Node *goal);

        // Function to generate a map with obstacles and player/enemy positions
        std::vector<std::vector<int>> generateMap(int rows, int cols, std::pair<int, int> enemyPos, std::pair<int, int> playerPos, const std::vector<std::pair<int, int>>& obstacles);

        // Function to get grid coordinates based on pixel coordinates
        std::pair<int, int> getGridCoordinates(int x, int y, int cellWidth, int cellHeight);

        // Function that returns both grid coordinates (row, column) and pixel coordinates (x, y)
        std::pair<std::pair<int, int>, std::pair<int, int>> getPathElementInBothForms(int row, int col, int pixelSize);

        // Function to get a list of path elements, each containing both grid and pixel coordinates
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getPathWithCoordinates(const std::vector<Node*>& path, int pixelSize);

        // Function to get obstacle grid points from obstacles
        std::vector<std::pair<int, int>> getObstaclePoints(int cellWidth, int cellHeight, std::vector<Obstacle *> obstacleVector);

        // Function to run the A* algorithm
        void runAStar(float playfieldWidth, float playfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector);

        void reset_AStar(float newPlayfieldWidth, float newPlayfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector);
        
        std::vector<float> getNextNode();
        std::vector<Node *> getPath();

        void printMapUtil(float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector);

};


#endif // ASTAR_H
