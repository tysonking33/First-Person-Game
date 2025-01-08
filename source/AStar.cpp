#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include "../includes/AStar.h"
#include <random>


using namespace std;

// Node constructor definition
Node::Node(int x, int y, int g, int h, Node *parent)
    : x(x), y(y), g(g), h(h), parent(parent) {}

// Node::f() returns the total cost f = g + h
int Node::f() const
{
    return g + h;
}

// Overload the 'greater than' operator to compare nodes in a priority queue
bool Node::operator>(const Node &other) const
{
    return f() > other.f();
}

// Directions for movement: 8 directions (up, down, left, right, and 4 diagonals)
const vector<pair<int, int>> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1} // Down-right, Down-left, Up-right, Up-left (diagonals)
};

// Check if a position is within bounds and not an obstacle
bool AStar::isValid(int x, int y, int rows, int cols, const vector<vector<int>> &grid)
{
    return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] != 1;
}

// Heuristic function: Chebyshev distance (max of horizontal and vertical distance)
int AStar::heuristic(int x1, int y1, int x2, int y2)
{
    return max(abs(x1 - x2), abs(y1 - y2)); // Chebyshev distance for 8-direction movement
}



// A* algorithm to find the shortest path
vector<Node *> AStar::aStar(const vector<vector<int>> &grid, Node *start, Node *goal)
{
    int rows = grid.size();
    int cols = grid[0].size();

    // Priority queue to hold nodes with the smallest f values (min-heap)
    priority_queue<Node *, vector<Node *>, greater<Node *>> openList;
    unordered_set<string> closedList;

    openList.push(start);

    while (!openList.empty())
    {
        Node *current = openList.top();
        openList.pop();

        // If we reach the goal, reconstruct the path
        if (current->x == goal->x && current->y == goal->y)
        {
            vector<Node *> path;
            while (current != nullptr)
            {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end()); // Reverse the path to get it from start to goal
            return path;
        }

        // Mark this node as visited
        closedList.insert(to_string(current->x) + "," + to_string(current->y));

        // Explore all possible directions (including diagonals)
        for (const auto &dir : directions)
        {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            // Check if the new position is valid and not already visited
            if (isValid(newX, newY, rows, cols, grid) &&
                closedList.find(to_string(newX) + "," + to_string(newY)) == closedList.end())
            {

                int newG = current->g + 1;                          // g cost (distance from the start node)
                int newH = heuristic(newX, newY, goal->x, goal->y); // h cost (heuristic)
                Node *neighbor = new Node(newX, newY, newG, newH, current);
                openList.push(neighbor);
            }
        }
    }

    return {}; // No path found
}

// Function to print the grid with the path marked
void AStar::printMapWithPath(const vector<vector<int>> &grid, const vector<Node *> &path, Node *start, Node *goal)
{
    if (path.empty()) return;
    if (grid.empty()) return;

    // Create a copy of the grid to work on
    vector<vector<int>> mapWithPath = grid;

    // Mark the path on the map
    for (auto node : path)
    {
        if (node->x >= 0 && node->x < mapWithPath.size() && node->y >= 0 && node->y < mapWithPath[0].size()) {
            if (mapWithPath[node->x][node->y] != 3 && mapWithPath[node->x][node->y] != 4) {
                mapWithPath[node->x][node->y] = 2;
            }
        }
    }

    // Mark the start (Enemy) and goal (Player) positions
    if (start->x < mapWithPath.size() && start->y < mapWithPath[0].size())
    {
        mapWithPath[start->x][start->y] = 4;
    }
    else
    {
        //std::cout << "(start->x >= mapWithPath.size() && start->y >= mapWithPath[0].size())\n";
        return ;
    }

    if (goal->x < mapWithPath.size() && goal->y < mapWithPath[0].size())
    {
        mapWithPath[goal->x][goal->y] = 3;
    }
    else
    {
        //std::cout << "(goal->x >= mapWithPath.size() && goal->y >= mapWithPath[0].size())\n";
        return ;
    }

    // Store previous map state for comparison
    static vector<vector<int>> previousMapWithPath;

    // Check if the map has changed
    if (mapWithPath != previousMapWithPath)
    {
        // Print the updated map with the path
        for (int i = 0; i < mapWithPath.size(); i++)
        {
            for (int j = 0; j < mapWithPath[i].size(); ++j)
            {
                if (mapWithPath[i][j] == 0) {
                    std::cout << ". "; // Empty space
                } else if (mapWithPath[i][j] == 1) {
                    std::cout << "# "; // Obstacle
                } else if (mapWithPath[i][j] == 2) {
                    std::cout << "x "; // Path
                } else if (mapWithPath[i][j] == 3) {
                    std::cout << "P "; // Player
                } else if (mapWithPath[i][j] == 4) {
                    std::cout << "E "; // Enemy
                }
            }
            std::cout << std::endl;
        }

        // Update previous map state after printing
        previousMapWithPath = mapWithPath;
    }
}


vector<vector<int>> AStar::generateMap(int rows, int cols, pair<int, int> enemyPos, pair<int, int> playerPos, const vector<pair<int, int>> &obstacles)
{
    // Initialize the map with all empty spaces (0)
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // Place obstacles on the map (1 represents obstacles)
    for (const auto &obs : obstacles)
    {
        int x = obs.first;
        int y = obs.second;
        if (x >= 0 && x < rows && y >= 0 && y < cols)
        {
            grid[x][y] = 1; // Marking obstacle
        }
    }

    // Place the enemy on the map (4 represents the enemy)
    int ex = enemyPos.first;
    int ey = enemyPos.second;
    if (ex >= 0 && ex < rows && ey >= 0 && ey < cols)
    {
        grid[ex][ey] = 4; // Marking enemy
    }

    // Place the player on the map (3 represents the player)
    int px = playerPos.first;
    int py = playerPos.second;
    if (px >= 0 && px < rows && py >= 0 && py < cols)
    {
        grid[px][py] = 3; // Marking player
    }

    return grid;
}

std::pair<int, int> AStar::getGridCoordinates(int x, int y, int cellWidth, int cellHeight)
{
    return std::make_pair(ceil(x / (float)cellWidth), ceil(y / (float)cellHeight));
}

// Function that returns both grid coordinates (row, column) and pixel coordinates (x, y)
// The pixel size is assumed to be fixed (e.g., 32x32 pixels per grid cell)
std::pair<std::pair<int, int>, std::pair<int, int>> AStar::getPathElementInBothForms(int row, int col, int pixelSize)
{
    // Grid coordinates are just (row, col)
    // Pixel coordinates are (col * pixelSize, row * pixelSize) assuming top-left origin
    int pixelX = col * pixelSize;
    int pixelY = row * pixelSize;

    return {{row, col}, {pixelX, pixelY}};
}

// Function that returns a list of path elements, each containing both grid and pixel coordinates
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> AStar::getPathWithCoordinates(const std::vector<Node *> &path, int pixelSize)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pathWithCoordinates;

    for (const Node *node : path)
    {
        // Get the pair from getPathElementInBothForms
        std::pair<std::pair<int, int>, std::pair<int, int>> pathElement = getPathElementInBothForms(node->x, node->y, pixelSize);

        // Manually unpack the grid and pixel coordinates
        std::pair<int, int> gridCoord = pathElement.first;
        std::pair<int, int> pixelCoord = pathElement.second;

        // Store the grid and pixel coordinates as a pair of pairs
        pathWithCoordinates.push_back(std::make_pair(gridCoord, pixelCoord));
    }

    return pathWithCoordinates;
}

std::vector<std::pair<int, int>> AStar::getObstaclePoints(int cellWidth, int cellHeight, std::vector<Obstacle *> obstacleVector)
{
    std::vector<std::pair<int, int>> gridCells; // resulting obstacle grid cells
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
            std::pair<int, int> gridPoint = getGridCoordinates(static_cast<int>(point.x), static_cast<int>(point.z), cellWidth, cellHeight);

            // Update the bounding box
            minX = std::min(minX, gridPoint.first);
            maxX = std::max(maxX, gridPoint.first);
            minY = std::min(minY, gridPoint.second);
            maxY = std::max(maxY, gridPoint.second);
        }

        // Now, generate all the grid cells within the bounding box
        for (int x = minX; x <= maxX; ++x)
        {
            for (int y = minY; y <= maxY; ++y)
            {
                gridCells.push_back(std::pair(x, y));
            }
        }
    }

    return gridCells;
}

void AStar::runAStar(float playfieldWidth, float playfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector)
{
    gridWidth = ceil(playfieldWidth / cellWidth);
    gridHeight = ceil(playfieldHeight / cellHeight);          // grid dimensions in rows and cols

    std::cout << "Grid Width: " << gridWidth << std::endl;
    std::cout << "Grid Height: " << gridHeight << std::endl;

    // Define the positions of the enemy and player
    pair<int, int> enemyPos = getGridCoordinates(enemyX, enemyY, cellWidth, cellHeight);    // Enemy's grid position
    pair<int, int> playerPos = getGridCoordinates(playerX, playerY, cellWidth, cellHeight); // Player's grid position

    // Define the obstacle positions
    vector<pair<int, int>> obstacles = getObstaclePoints(cellWidth, cellHeight, obstacleVector);

    // Generate the map based on the given parameters
    vector<vector<int>> grid = generateMap(gridHeight, gridWidth, enemyPos, playerPos, obstacles);

    Node *start = new Node(enemyPos.first, enemyPos.second);  // Enemy's starting position
    Node *goal = new Node(playerPos.first, playerPos.second); // Player's position

    // Perform A* algorithm to find the path
    path = aStar(grid, start, goal);

    // Print the map with the path
    if (!path.empty())
    {
        std::cout << "Path found:" << std::endl;
        printMapWithPath(grid, path, start, goal);
    }
    else
    {
        std::cout << "No path found!" << std::endl;
        printMapWithPath(grid, path, start, goal);
    }
}

void AStar::printMapUtil(float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector)
{
    gridWidth = ceil(playfieldWidth / cellWidth);
    gridHeight = ceil(playfieldHeight / cellHeight);          // grid dimensions in rows and cols


    // Define the positions of the enemy and player
    pair<int, int> enemyPos = getGridCoordinates(enemyX, enemyY, cellWidth, cellHeight);    // Enemy's grid position
    pair<int, int> playerPos = getGridCoordinates(playerX, playerY, cellWidth, cellHeight); // Player's grid position

    // Define the obstacle positions
    vector<pair<int, int>> obstacles = getObstaclePoints(cellWidth, cellHeight, obstacleVector);

    // Generate the map based on the given parameters
    vector<vector<int>> grid = generateMap(gridHeight, gridWidth, enemyPos, playerPos, obstacles);

    Node *start = new Node(enemyPos.first, enemyPos.second);  // Enemy's starting position
    Node *goal = new Node(playerPos.first, playerPos.second); // Player's position


    // Print the map with the path
    if (!path.empty())
    {
        printMapWithPath(grid, path, start, goal);
    }
    else
    {
        printMapWithPath(grid, path, start, goal);
    }

}


std::vector<float> AStar::getNextNode()
{
    std::vector<float> result;
    // Extract the first node from the path and convert it to pixel coordinates
    if (path.size() > current_node+1)
    {
        std::pair<int, int> gridCoord = {path[current_node]->x, path[current_node]->y};  // Get grid coordinates of the first node in path
        std::pair<int, int> pixelCoord = getPathElementInBothForms(gridCoord.first, gridCoord.second, cellWidth).second;
        result.push_back(float(pixelCoord.first));
        result.push_back(float(pixelCoord.second));
    }
    else
    {
        std::cout << "reached end of path\n";
        //std::random_device rd;
        //std::mt19937 gen(rd());

        //std::uniform_real_distribution<> dis(1.0, 19.0);

        //result.push_back(dis(gen));
        //result.push_back(dis(gen));
    }
    current_node++;

    return result;
}


AStar::AStar(float newPlayfieldWidth, float newPlayfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector)
{
    playfieldWidth = newPlayfieldWidth;
    playfieldHeight = newPlayfieldHeight;
    cellWidth = 1;
    cellHeight = 1;
    gridWidth = ceil(playfieldWidth / cellWidth);
    gridHeight = ceil(playfieldHeight / cellHeight);
    current_node = 0;
    runAStar(playfieldWidth, playfieldHeight, playerX, playerY, enemyX, enemyY, obstacleVector);
}

void AStar::reset_AStar(float newPlayfieldWidth, float newPlayfieldHeight, float playerX, float playerY, float enemyX, float enemyY, std::vector<Obstacle *> obstacleVector)
{
    current_node = 0;
    runAStar(playfieldWidth, playfieldHeight, playerX, playerY, enemyX, enemyY, obstacleVector);

}

std::vector<Node *> AStar::getPath()
{
    return path;
}
