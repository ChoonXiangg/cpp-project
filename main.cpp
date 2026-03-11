#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "Grid.h"
#include "GridNode.h"
#include "Display.h"
#include "Pathfinding.h"

int main() {
    Display::EnableAnsiEscapes();

    // 1. Grid dimensions
    int width, height;
    std::cout << "Enter grid height and width: ";
    std::cin >> height >> width;

    Grid grid(width, height);

    // 2. Start and end positions
    int sx, sy, ex, ey;
    std::cout << "Enter start position (x, y): ";
    std::cin >> sx >> sy;
    std::cout << "Enter end position (x, y): ";
    std::cin >> ex >> ey;

    GridNode* start = grid.GetNode(sx, sy);
    GridNode* target = grid.GetNode(ex, ey);

    // 3. Number of walls
    int wallCount;
    std::cout << "Enter number of walls: ";
    std::cin >> wallCount;

    // 4. Wall positions
    for (int i = 0; i < wallCount; i++) {
        int wx, wy;
        std::cout << "Enter wall " << (i + 1) << " position (x, y): ";
        std::cin >> wx >> wy;
        grid.SetWall(wx, wy);
    }

    // Find path
    std::vector<NodeBase*> basePath = Pathfinding::FindPath(start, target);

    if (basePath.empty()) {
        std::cout << "No path found.\n";
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