#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <functional>
#include <algorithm>

using namespace std;

// Struct to represent a node in the grid
struct Node
{
    int x, y;     // Position of the node
    int g, h;     // g is the cost to reach the node, h is the heuristic (estimated cost to goal)
    Node *parent; // Pointer to the parent node

    // Constructor
    Node(int x, int y, int g = 0, int h = 0, Node *parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    // f = g + h, used to sort nodes in priority queue
    int f() const { return g + h; }

    bool operator>(const Node &other) const
    {
        return f() > other.f();
    }
};

// Directions for movement: 8 directions (up, down, left, right, and 4 diagonals)
const vector<pair<int, int>> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1} // Down-right, Down-left, Up-right, Up-left (diagonals)
};

// Check if a position is within bounds and not an obstacle
bool isValid(int x, int y, int rows, int cols, const vector<vector<int>> &grid)
{
    return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] != 1;
}

// Heuristic function: Chebyshev distance (max of horizontal and vertical distance)
int heuristic(int x1, int y1, int x2, int y2)
{
    return max(abs(x1 - x2), abs(y1 - y2)); // Chebyshev distance for 8-direction movement
}

// A* algorithm to find the shortest path
vector<Node *> aStar(const vector<vector<int>> &grid, Node *start, Node *goal)
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
void printMapWithPath(const vector<vector<int>> &grid, const vector<Node *> &path, Node *start, Node *goal)
{
    // Create a copy of the grid to mark the path
    vector<vector<int>> mapWithPath = grid;

    // Mark the path with 'x'
    for (auto node : path)
    {
        // Don't overwrite 'P' (Player) or 'E' (Enemy)
        if (mapWithPath[node->x][node->y] != 3 && mapWithPath[node->x][node->y] != 4)
        {
            mapWithPath[node->x][node->y] = 2; // 'x' for path
        }
    }

    // Mark the start (Enemy) and goal (Player) positions
    mapWithPath[start->x][start->y] = 4; // Mark 'E' for the enemy
    mapWithPath[goal->x][goal->y] = 3;   // Mark 'P' for the player

    // Print the grid with the path
    for (int i = 0; i < mapWithPath.size(); ++i)
    {
        for (int j = 0; j < mapWithPath[i].size(); ++j)
        {
            if (mapWithPath[i][j] == 0)
            {
                cout << ". "; // Empty space
            }
            else if (mapWithPath[i][j] == 1)
            {
                cout << "# "; // Obstacle
            }
            else if (mapWithPath[i][j] == 2)
            {
                cout << "x "; // Path
            }
            else if (mapWithPath[i][j] == 3)
            {
                cout << "P "; // Player (P)
            }
            else if (mapWithPath[i][j] == 4)
            {
                cout << "E "; // Enemy (E)
            }
        }
        cout << endl;
    }
}

vector<vector<int>> generateMap(int rows, int cols, pair<int, int> enemyPos, pair<int, int> playerPos, const vector<pair<int, int>>& obstacles) {
    // Initialize the map with all empty spaces (0)
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    
    // Place obstacles on the map (1 represents obstacles)
    for (const auto& obs : obstacles) {
        int x = obs.first;
        int y = obs.second;
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            grid[x][y] = 1; // Marking obstacle
        }
    }

    // Place the enemy on the map (4 represents the enemy)
    int ex = enemyPos.first;
    int ey = enemyPos.second;
    if (ex >= 0 && ex < rows && ey >= 0 && ey < cols) {
        grid[ex][ey] = 4; // Marking enemy
    }

    // Place the player on the map (3 represents the player)
    int px = playerPos.first;
    int py = playerPos.second;
    if (px >= 0 && px < rows && py >= 0 && py < cols) {
        grid[px][py] = 3; // Marking player
    }

    return grid;
}

std::pair<int, int> getGridCoordinates(int x, int y, int cellWidth, int cellHeight)
{
    return std::make_pair(ceil(x / (float)cellWidth), ceil(y / (float)cellHeight));
}

// Function that returns both grid coordinates (row, column) and pixel coordinates (x, y)
// The pixel size is assumed to be fixed (e.g., 32x32 pixels per grid cell)
std::pair<std::pair<int, int>, std::pair<int, int>> getPathElementInBothForms(int row, int col, int pixelSize) {
    // Grid coordinates are just (row, col)
    // Pixel coordinates are (col * pixelSize, row * pixelSize) assuming top-left origin
    int pixelX = col * pixelSize;
    int pixelY = row * pixelSize;

    return {{row, col}, {pixelX, pixelY}};
}

// Function that returns a list of path elements, each containing both grid and pixel coordinates
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getPathWithCoordinates(const std::vector<Node*>& path, int pixelSize) {
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pathWithCoordinates;
    
    for (const Node* node : path) {
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

std::vector<std::pair<int, int>> getObstaclePoints(int cellWidth, int cellHeight, std::vector<Obstacle *> obstacleVector)
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

int main()
{

    {
        int playfieldWidth = 20;
        int playfieldHeight = 20;
        int cellWidth = 4, cellHeight = 4;                                                                     // cell dimension in pixels
        int gridWidth = ceil(playfieldWidth / cellWidth)+1, gridHeight = ceil(playfieldHeight/ cellHeight)+1; //grid dimensions in rows and cols

        std::cout << "Grid Width: " << gridWidth << std::endl;
        std::cout << "Grid Height: " << gridHeight << std::endl;

        int enemyPixelPosX = 0, enemyPixelPosY = 0; 
        int playerPixelPosX = 20, playerPixelPosY = 20; 
        // Define the positions of the enemy and player
        pair<int, int> enemyPos = getGridCoordinates(enemyPixelPosX, enemyPixelPosY, cellWidth, cellHeight); //top left
        pair<int, int> playerPos = getGridCoordinates(playerPixelPosX, playerPixelPosY, cellWidth, cellHeight); //bottom right

        // Define the obstacle positions
        vector<pair<int, int>> obstacles = getObstaclePoints(cellWidth, cellHeight, obstacleVector);


        // Generate the map based on the given parameters
        vector<vector<int>> grid = generateMap(gridHeight, gridWidth, enemyPos, playerPos, obstacles);

        Node *start = new Node(enemyPos.first, enemyPos.second); // Enemy's starting position
        Node *goal = new Node(playerPos.first, playerPos.second);  // Player's position

        // Perform A* algorithm to find the path
        vector<Node *> path = aStar(grid, start, goal);

        // Print the map with the path
        if (!path.empty())
        {
            cout << "Path found:" << endl;
            printMapWithPath(grid, path, start, goal);
        }
        else
        {
            cout << "No path found!" << endl;
            return ;
        }

        // Get the path with both grid and pixel coordinates
        vector<pair<pair<int, int>, pair<int, int>>> pathWithCoordinates = getPathWithCoordinates(path, cellWidth);

        std::cout << "Path with grid and pixel coordinates:" << endl;
        for (const std::pair<std::pair<int, int>, std::pair<int, int>>& pathElement : pathWithCoordinates) {
            // Manually unpack grid and pixel coordinates
            std::pair<int, int> gridCoord = pathElement.first;
            std::pair<int, int> pixelCoord = pathElement.second;

            // Unpack the grid and pixel coordinates further into row, col, pixelX, pixelY
            int row = gridCoord.first;
            int col = gridCoord.second;
            int pixelX = pixelCoord.first;
            int pixelY = pixelCoord.second;

            // Print the values (you can replace this with any other logic)
            std::cout << "Grid Coordinates: (" << row << ", " << col << ")\n";
            std::cout << "Pixel Coordinates: (" << pixelX << ", " << pixelY << ")\n";
        }


        std::pair<int, int> gridCoord = pathWithCoordinates[1].first;
        std::pair<int, int> pixelCoord = pathWithCoordinates[1].second;

        // Unpack the grid and pixel coordinates further into row, col, pixelX, pixelY
        int row = gridCoord.first;
        int col = gridCoord.second;
        int pixelX = pixelCoord.first;
        int pixelY = pixelCoord.second;

        // Print the values (you can replace this with any other logic)
        std::cout << "Grid Coordinates: (" << row << ", " << col << ")\n";
        std::cout << "Pixel Coordinates: (" << pixelX << ", " << pixelY << ")\n";

        delete start;
        delete goal;
    }

    return 0;
}
