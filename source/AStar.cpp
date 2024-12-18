#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "../includes/AStar.h"

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point &p) const
        {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1); // Combine the hashes of x and y
        }
    };
}

// Convert pixel coordinates to grid coordinates
Point getGridCoordinates(int x, int y, int cellWidth, int cellHeight)
{
    return Point(ceil(x / cellWidth), ceil(y / cellHeight));
}

// Heuristic function: Manhattan distance (for diagonal movement, we use Chebyshev distance)
int heuristic(const Point &a, const Point &b)
{
    return max(abs(a.x - b.x), abs(a.y - b.y)); // Chebyshev distance for diagonal movement
}

// A* Algorithm for pathfinding
vector<Point> astar(const Point &start, const Point &goal, const vector<vector<int>> &grid, int cellWidth, int cellHeight)
{
    // Define the directions: left, right, up, down, and diagonal movements
    vector<Point> directions = {
        Point(-1, 0),  // left
        Point(1, 0),   // right
        Point(0, -1),  // up
        Point(0, 1),   // down
        Point(-1, -1), // top-left diagonal
        Point(1, -1),  // top-right diagonal
        Point(-1, 1),  // bottom-left diagonal
        Point(1, 1)    // bottom-right diagonal
    };

    // Open list (priority queue), stores (f_cost, point)
    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> openList;
    openList.push({heuristic(start, goal), start});

    // Maps to track costs
    unordered_map<Point, int> gCost;
    unordered_map<Point, int> fCost;
    unordered_map<Point, Point> cameFrom;

    gCost[start] = 0;
    fCost[start] = heuristic(start, goal);

    // Closed list to avoid revisiting
    set<Point> closedList;

    while (!openList.empty())
    {
        // Get the node with the lowest f_cost
        Point current = openList.top().second;
        openList.pop();

        // If we reached the goal, reconstruct the path
        if (current == goal)
        {
            vector<Point> path;
            while (cameFrom.find(current) != cameFrom.end())
            {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        closedList.insert(current);

        // Check all neighbors (including diagonal movements)
        for (const Point &direction : directions)
        {
            Point neighbor(current.x + direction.x, current.y + direction.y);

            // Make sure the neighbor is within bounds and not an obstacle
            if (neighbor.x < 0 || neighbor.x >= grid.size() || neighbor.y < 0 || neighbor.y >= grid[0].size())
            {
                continue;
            }

            if (grid[neighbor.x][neighbor.y] == 1)
            { // 1 is an obstacle
                continue;
            }

            // If the neighbor is already in the closed list, skip it
            if (closedList.find(neighbor) != closedList.end())
            {
                continue;
            }

            int tentativeG = gCost[current] + ((direction.x == 0 || direction.y == 0) ? 1 : 14); // Diagonal cost is 14, straight is 1

            // If this path is better or the neighbor hasn't been visited
            if (gCost.find(neighbor) == gCost.end() || tentativeG < gCost[neighbor])
            {
                gCost[neighbor] = tentativeG;
                fCost[neighbor] = gCost[neighbor] + heuristic(neighbor, goal);
                cameFrom[neighbor] = current;
                openList.push({fCost[neighbor], neighbor});
            }
        }
    }

    // If no path found
    return {};
}

// Function to create the game map dynamically
vector<vector<int>> createGameMap(int width, int height, double obstacleProbability)
{
    vector<vector<int>> map(height, vector<int>(width));
    srand(time(0)); // Seed for random number generation

    // Fill the map with random obstacles and free space (0 for free, 1 for obstacle)
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (rand() % 100 < obstacleProbability * 100)
            {
                map[i][j] = 1; // Obstacle
            }
            else
            {
                map[i][j] = 0; // Free space
            }
        }
    }

    return map;
}

// Function to print the game map with symbols
void printGameMap(const vector<vector<int>> &gameMap, const Point &start, const Point &goal, const vector<Point> &path)
{
    int height = gameMap.size();
    int width = gameMap[0].size();

    // Create a copy of the game map to modify for display
    vector<vector<char>> displayMap(height, vector<char>(width, ' '));

    // Place obstacles on the map
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (gameMap[i][j] == 1)
            {
                displayMap[i][j] = '1'; // Obstacle
            }
        }
    }

    // Place the player and enemy, ensuring the positions are within bounds
    if (start.x >= 0 && start.x < height && start.y >= 0 && start.y < width)
    {
        displayMap[start.x][start.y] = 'e'; // Enemy
    }
    if (goal.x >= 0 && goal.x < height && goal.y >= 0 && goal.y < width)
    {
        displayMap[goal.x][goal.y] = 'p'; // Player
    }

    // Mark the path with 'x', excluding the start and goal positions
    for (const Point &p : path)
    {
        if (p != start && p != goal)
        { // Don't overwrite the start or goal
            displayMap[p.x][p.y] = 'x';
        }
    }

    // Print the map
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (displayMap[i][j] == ' ')
            {
                displayMap[i][j] = '0'; // Empty space
            }
            cout << displayMap[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to convert grid coordinates to pixel coordinates
Point getPixelCoordinates(const Point &gridPoint, int cellWidth, int cellHeight)
{
    return Point(gridPoint.x * cellWidth, gridPoint.y * cellHeight);
}

// Function to get the first step in both game map coordinates and pixel coordinates
std::vector<Point> getFirstStep(const vector<Point> &path, int cellWidth, int cellHeight)
{
    if (path.empty())
    {
        cout << "No path found!" << endl;
        std::vector<Point> result;
        return result;
    }

    // First step in the game map (grid coordinates)
    Point firstStepGameMap = path[0];

    // First step in pixel coordinates
    Point firstStepPixel = getPixelCoordinates(firstStepGameMap, cellWidth, cellHeight);

    // Output the results
    cout << "First step (Game Map Coordinates): (" << firstStepGameMap.x << ", " << firstStepGameMap.y << ")" << endl;
    cout << "First step (Pixel Coordinates): (" << firstStepPixel.x << ", " << firstStepPixel.y << ")" << endl;

    std::vector<Point> result;
    result.push_back(firstStepGameMap);
    result.push_back(firstStepPixel);

    return result;
}

std::vector<Point> getObstaclePoints(int cellWidth, int cellHeight, std::vector<Obstacle *> obstacleVector)
{
    std::vector<Point> gridCells; // resulting obstacle grid cells
    for (auto obstacle : obstacleVector)
    {
        // Get the 8 points of the cuboid
        std::vector<glm::vec3> cuboidPoints = obstacle->getCuboidPoints();

        // Variables to track the min/max grid coordinates
        int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;

        // Convert each cuboid point to grid coordinates and find the bounding box
        for (const glm::vec3 &point : cuboidPoints)
        {
            // For simplicity, we'll use the X and Z coordinates as the 2D grid coordinates
            // (ignoring Y in this example)
            Point gridPoint = getGridCoordinates(static_cast<int>(point.x), static_cast<int>(point.z), cellWidth, cellHeight);

            // Update the bounding box
            minX = std::min(minX, gridPoint.x);
            maxX = std::max(maxX, gridPoint.x);
            minY = std::min(minY, gridPoint.y);
            maxY = std::max(maxY, gridPoint.y);
        }

        // Now, generate all the grid cells within the bounding box
        for (int x = minX; x <= maxX; ++x)
        {
            for (int y = minY; y <= maxY; ++y)
            {
                gridCells.push_back(Point(x, y));
            }
        }
    }

    return gridCells;
}

std::vector<float> runAStar(float playfieldWidth, float playfieldHeight, float playerX, float playerY, float enemyX, int enemyY, std::vector<Obstacle *> obstacleVector)
{
    std::cout << "playerX: " << playerX << ", playerY: " << playerY << std::endl;
    std::cout << "enemyX: " << enemyX << ", enemyY: " << enemyY << std::endl;
    // Map dimensions
    int cellWidth = 1, cellHeight = 1;                                                                     // Each cell is cellWidth by cellHeight pixels
    int gridWidth = ceil(playfieldWidth / cellWidth)+1, gridHeight = ceil(playfieldHeight/ cellHeight)+1; // 10x10 grid

    std::cout << "1. gridWidth: " << gridWidth << ", gridHeight: " << gridHeight << std::endl;

    // Create the game map dynamically (with random obstacles)
    vector<vector<int>> gameMap = createGameMap(gridWidth, gridWidth, 0); // 30% obstacles

    // Starting and goal positions in pixel coordinates
    Point enemyPosition((int)enemyX, (int)enemyY);    // Enemy at pixel (12, 14)
    Point playerPosition((int)playerX, (int)playerY); // Player at pixel (60, 30)

    // Convert pixel positions to grid coordinates
    Point start = getGridCoordinates(enemyPosition.x, enemyPosition.y, cellWidth, cellHeight);

    Point goal = getGridCoordinates(playerPosition.x, playerPosition.y, cellWidth, cellHeight);

    /*-------------------------------------start adding obstacles--------------------------------------------------*/
    std::vector<Point> gridCells =  getObstaclePoints(cellWidth, cellHeight, obstacleVector);// resulting obstacle grid cells

    for (auto obstacleGridCell: gridCells)
    {
        gameMap[obstacleGridCell.x][obstacleGridCell.y] = 1;
    }

    /*-------------------------------------finished adding obstacles-----------------------------------------------*/

    // Find the path from enemy to player
    vector<Point> path = astar(start, goal, gameMap, cellWidth, cellHeight);

    // If no path is found, inform the user and terminate
    if (path.empty())
    {
        cout << "No path found!" << endl;
        // return 1;
        // Output the generated game map
        cout << "Generated Game Map:\n";
        printGameMap(gameMap, start, goal, path);
        std::vector<float> nextPix;
        return nextPix;
    }

    std::cout << "playfieldWidth: " << playfieldWidth << ", playfieldHeight: " << playfieldHeight << std::endl;
    std::cout << "cellWidth: " << cellWidth << ", cellHeight: " << cellHeight << std::endl;
    std::cout << "gridWidth: " << gridWidth << ", gridHeight: " << gridHeight << std::endl;


    std::vector<Point> result = getFirstStep(path, cellWidth, cellHeight);

    std::vector<float> nextPix{(float)result[1].x, (float)result[1].y};

    return nextPix;
}
