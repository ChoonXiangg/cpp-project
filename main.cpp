#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
#include "GridNode.h"
#include "Display.h"
#include "Pathfinding.h"

int main() {
    Display::EnableAnsiEscapes();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 1. Grid dimensions
    int width, height;
    std::cout << "Enter grid width and height: ";
    std::cin >> width >> height;

    Grid grid(width, height);

    // 2. Start and end positions
    int sx, sy, ex, ey;
    std::cout << "Start position (x, y): ";
    std::cin >> sx >> sy;
    std::cout << "End position (x, y): ";
    std::cin >> ex >> ey;

    GridNode* start = grid.GetNode(sx, sy);
    GridNode* target = grid.GetNode(ex, ey);

    // 3. Number of walls
    int wallCount;
    std::cout << "Number of walls: ";
    std::cin >> wallCount;

    // 4. Manual or random wall placement
    int choice;
    std::cout << "Wall position (1: Manual, 2: Random): ";
    std::cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < wallCount; i++) {
            int wx, wy;
            std::cout << "Wall " << (i + 1) << " position (x, y): ";
            std::cin >> wx >> wy;
            grid.SetWall(wx, wy);
        }
    }
    else {
        int placed = 0;
        while (placed < wallCount) {
            int wx = std::rand() % width;
            int wy = std::rand() % height;

            GridNode* node = grid.GetNode(wx, wy);

            // Don't place walls on start, target, or existing walls
            if (node == start || node == target || !node->IsWalkable())
                continue;

            grid.SetWall(wx, wy);
            placed++;
        }
    }

    // Find path
    std::vector<NodeBase*> basePath = Pathfinding::FindPath(start, target);

    if (basePath.empty()) {
        std::cout << "\n";
        std::vector<GridNode*> empty;
        Display::PrintGrid(grid, start, target, start, empty);
        std::cout << "\nNo path found.\n";
        return 0;
    }

    std::vector<GridNode*> path;
    path.reserve(basePath.size());
    for (NodeBase* node : basePath) {
        path.push_back(static_cast<GridNode*>(node));
    }
    std::reverse(path.begin(), path.end());

    std::cout << "\nS: Start  E: End  .: Free  X: Wall  @: Agent  *: Path\n";
    std::cout << "Press any key to take a step\n\n";

    // Show initial state
    std::vector<GridNode*> visited;
    Display::PrintGrid(grid, start, target, start, visited);

    for (int i = 0; i < (int)path.size(); i++) {
        int ch = _getch();
        (void)ch;

        GridNode* agent = path[i];

        if (i == 0)
            visited.push_back(start);
        else
            visited.push_back(path[i - 1]);

        Display::MoveCursorUp(grid.GetHeight());
        Display::PrintGrid(grid, start, target, agent, visited);
    }

    // Print the full path
    std::cout << "\nPath: (" << start->x_ << ", " << start->y_ << ")";
    for (GridNode* node : path) {
        std::cout << ", (" << node->x_ << ", " << node->y_ << ")";
    }
    std::cout << "\nPath length: " << path.size() << "\n";

    return 0;
}