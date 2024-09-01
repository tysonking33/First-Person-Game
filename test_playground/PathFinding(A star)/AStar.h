#ifndef ASTAR_H
#define ASTAR_H

// Include standard libraries
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>    // Use <cmath> instead of <math.h> for C++
#include <set>
#include <queue>

// Define constants
#define M_PI 3.14159265358979323846

// Structure representing a cell in the grid
struct Cell
{
    float g;         // Movement cost from starting point to a given cell on the grid
    float h;         // Estimated movement cost from the given cell to the final destination
    float f;         // Sum of g and h
    Cell *parent;    // Pointer to the parent cell
    float x;         // X-coordinate
    float y;         // Y-coordinate
    float value;     // Cell value

    // Equality operator to compare Cell objects
    bool operator==(const Cell &other) const
    {
        return x == other.x && y == other.y && g == other.g &&
               h == other.h && f == other.f && parent == other.parent;
    }
};

// Structure representing a coordinate
struct Coordinate
{
    float x;               // X-coordinate
    float y;               // Y-coordinate
    float angleToNext;     // Angle to the next coordinate (in degrees)
};

// Class representing the A* algorithm
class AStar
{
public:
    // Constructor
    AStar(float newMapHeightPx, float newMapWidthPx, float newMapHeightCount, float newMapWidthCount);

    // Public methods
    float euclideanDistance(Cell currentCell, Cell otherCell);
    Cell findLowestF(std::vector<Cell> &openList);
    std::vector<Cell> findSuccessor(std::vector<std::vector<int>> &map, Cell &currentCell, Cell start, Cell end);
    bool compareCells(Cell A, Cell B);
    bool checkEmptyCell(Cell A);
    Cell findCell(std::vector<Cell> cellList, Cell target);
    void printCell(std::string name, Cell a);
    bool areAllCellsEmpty(const std::vector<Cell> &openList);
    void AStarSearchBasic(std::vector<std::vector<int>> &map, Cell start, Cell end);
    void printPath();
    void translateIdxToCoords();

    // Member variables
    std::vector<Cell> finalPathIndex;       // Indices of the final path
    std::vector<Coordinate> finalPathCoords; // Coordinates of the final path

    float mapHeightPx;      // Height of the map in pixels
    float mapWidthPx;       // Width of the map in pixels
    float mapHeightCount;   // Height of the map in cell count
    float mapWidthCount;    // Width of the map in cell count
    float cellHeight;       // Height of a cell
    float cellWidth;        // Width of a cell
};


/*void AStarReactivePath
    check for 3 cell ahead, max, and conduct a star with neightbours 3 cells away, if any cells are blocking these cells, disqualify the cells

 */

#endif // ASTAR_H
