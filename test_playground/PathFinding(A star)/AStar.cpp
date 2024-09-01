#include "AStar.h"

float euclideanDistance(Cell currentCell, Cell otherCell)
{
    return sqrt(pow(currentCell.x - otherCell.x, 2) + pow(currentCell.y - otherCell.y, 2));
}

Cell findLowestF(std::vector<Cell> &openList)
{
    if (openList.empty())
    {
        std::cerr << "openList is empty\n";
        return Cell{-1, -1, -1, nullptr, -1, -1}; // Return an "empty" cell
    }

    auto minIt = openList.begin();
    for (auto iT = openList.begin(); iT != openList.end(); ++iT)
    {
        if (iT->f < minIt->f)
        {
            minIt = iT;
        }
    }

    Cell minFCell = *minIt;
    openList.erase(minIt);

    return minFCell;
}

std::vector<Cell> findSuccessor(std::vector<std::vector<int>> &map, Cell &currentCell, Cell start, Cell end)
{
    std::vector<Cell> successorVector;
    std::vector<std::vector<int>> neighbourMovements = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : neighbourMovements)
    {
        int neighbourX = move[0] + currentCell.x;
        int neighbourY = move[1] + currentCell.y;
        if (neighbourX >= 0 && neighbourX < static_cast<int>(map.size()) &&
            neighbourY >= 0 && neighbourY < static_cast<int>(map[0].size()))
        {
            if (map[neighbourX][neighbourY] == 1)
                continue; // This cell is blocked

            Cell newCell;
            newCell.x = neighbourX;
            newCell.y = neighbourY;
            newCell.parent = new Cell(currentCell); // Create a unique copy of currentCell for parent
            newCell.g = currentCell.g + euclideanDistance(currentCell, newCell);
            newCell.h = euclideanDistance(newCell, end);
            newCell.f = newCell.g + newCell.h;
            newCell.value = map[neighbourX][neighbourY];

            successorVector.push_back(newCell);
        }
    }

    return successorVector;
}

bool compareCells(Cell A, Cell B)
{
    return (A.x == B.x) && (A.y == B.y);
}

bool checkEmptyCell(Cell A)
{
    return A == Cell{-1, -1, -1, nullptr, -1, -1};
}

Cell findCell(std::vector<Cell> cellList, Cell target)
{
    for (auto iT = cellList.begin(); iT != cellList.end(); ++iT)
    {
        if (compareCells(*iT, target))
        {
            return *iT;
        }
    }
    return Cell{-1, -1, -1, nullptr, -1, -1};
}

void printCell(std::string name, Cell a)
{
    std::cout << "Printing Cell " << name << ") g: " << a.g << ", h: " << a.h << ", f: " << a.f
              << ", x: " << a.x << ", y: " << a.y << ", value: " << a.value << std::endl;
}

bool areAllCellsEmpty(const std::vector<Cell> &openList)
{
    Cell emptyCell{-1, -1, -1, nullptr, -1, -1};
    for (const auto &cell : openList)
    {
        if (!(cell == emptyCell))
        {
            return false;
        }
    }
    return true;
}

void AStar::AStarSearchBasic(std::vector<std::vector<int>> &map, Cell start, Cell end)
{
    std::vector<Cell> openList;   // Cells for discovery and have not been discovered yet
    std::vector<Cell> closedList; // Cells already evaluated

    openList.push_back(start);

    while (!openList.empty())
    {
        Cell q = findLowestF(openList);

        std::vector<Cell> successorVector = findSuccessor(map, q, start, end);

        for (auto &successor : successorVector)
        {
            // i) If successor is the goal, stop the search
            if (compareCells(successor, end))
            {
                std::cout << "Goal found!\n";

                // Backtrack from the end cell to the start cell
                Cell *current = &successor;
                while (current != nullptr)
                {
                    printCell("Current", *current);
                    finalPath.push_back(*current);
                    current = current->parent;
                }

                std::reverse(finalPath.begin(), finalPath.end());
                printPath(); // Call to print the path
                return;      // Correct exit
            }

            // ii) Compute g, h, and f for the successor
            successor.g = q.g + euclideanDistance(q, successor); // g cost from start to successor
            successor.h = euclideanDistance(successor, end);     // h cost (heuristic) from successor to end
            successor.f = successor.g + successor.h;             // total cost f

            // iii) Check if a better node exists in the OPEN list
            bool skipSuccessor = false;
            for (auto &openNode : openList)
            {
                if (compareCells(openNode, successor) && openNode.f <= successor.f)
                {
                    skipSuccessor = true;
                    break;
                }
            }

            // iv) Check if a better node exists in the CLOSED list
            if (!skipSuccessor)
            {
                for (auto &closedNode : closedList)
                {
                    if (compareCells(closedNode, successor) && closedNode.f <= successor.f)
                    {
                        skipSuccessor = true;
                        break;
                    }
                }
            }

            // If no better node exists, add the successor to the open list
            if (!skipSuccessor)
            {
                openList.push_back(successor);
                std::cout << "Added to openList: (" << successor.x << ", " << successor.y << ")\n";
            }
        }
        closedList.push_back(q);
        std::cout << "Moved to closedList: (" << q.x << ", " << q.y << ")\n";
    }

    std::cout << "No path found\n";
}

void AStar::printPath()
{
    std::cout << "Printing path\n";
    for (auto It = finalPath.begin(); It != finalPath.end(); It++)
    {
        std::cout << "(" << It->x << ", " << It->y << ")\n";
    }
    std::cout << "Finished printing path\n";
}
/*void AStarReactivePath
    check for 3 cell ahead, max, and conduct a star with neightbours 3 cells away, if any cells are blocking these cells, disqualify the cells

 */
