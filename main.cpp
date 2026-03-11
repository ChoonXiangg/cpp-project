#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "Grid.h"
#include "GridNode.h"
#include "Display.h"
#include "Pathfinding.h"

int layout[Grid::HEIGHT][Grid::WIDTH] = {
    { 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 },
};

int main() {
    Display::EnableAnsiEscapes();

    Grid grid(layout);
    GridNode* start = grid.GetNode(0, 0);
    GridNode* target = grid.GetNode(4, 4);

    // FindPath works with NodeBase* (generic), so we cast the result back to GridNode*
    std::vector<NodeBase*> basePath = Pathfinding::FindPath(start, target);

    if (basePath.empty()) {
        std::cout << "No path found.\n";
        return 0;
    }

    // Cast once at the boundary, then use GridNode* everywhere
    std::vector<GridNode*> path;
    path.reserve(basePath.size());
    for (NodeBase* node : basePath) {
        path.push_back(static_cast<GridNode*>(node));
    }

    // FindPath returns path in reverse (target -> start), so reverse it
    std::reverse(path.begin(), path.end());

    std::cout << "S: Start  E: End  .: Free  X: Wall  @: Agent  *: Path\n";
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

        Display::MoveCursorUp(Grid::HEIGHT);
        Display::PrintGrid(grid, start, target, agent, visited);
    }

    // Print the full path: start + path nodes
    std::cout << "\nPath: (" << start->x_ << ", " << start->y_ << ")";
    for (GridNode* node : path) {
        std::cout << ", (" << node->x_ << ", " << node->y_ << ")";
    }
    std::cout << "\nPath length: " << path.size() << "\n";

    return 0;
}