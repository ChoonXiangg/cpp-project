#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include "HexGrid.h"
#include "HexNode.h"
#include "Display.h"
#include "Pathfinding.h"
#include "runHexGrid.h"

void runHexGrid(int width, int height) {
    HexGrid grid(width, height);

    int sx, sy, ex, ey;
    std::cout << "Start position (x, y): ";
    std::cin >> sx >> sy;
    std::cout << "End position (x, y): ";
    std::cin >> ex >> ey;

    auto start = grid.GetNode(sx, sy);
    auto target = grid.GetNode(ex, ey);

    int wallCount;
    std::cout << "Wall amount: ";
    std::cin >> wallCount;

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
            auto node = grid.GetNode(wx, wy);
            if (node == start || node == target || !node->IsWalkable())
                continue;
            grid.SetWall(wx, wy);
            placed++;
        }
    }

    auto basePath = Pathfinding::FindPath(start, target);

    if (basePath.empty()) {
        std::cout << "\n";
        std::vector<HexNode*> empty;
        Display::PrintGrid(grid, start, target, start, empty);
        std::cout << "\nNo path found.\n";
        return;
    }

    // Transform NodeBase* to HexNode* using std::transform
    std::vector<HexNode*> path(basePath.size());
    std::transform(basePath.begin(), basePath.end(), path.begin(),
        [](NodeBase* node) { return static_cast<HexNode*>(node); });
    std::reverse(path.begin(), path.end());

    std::cout << "\nS: Start  E: End  .: Free  X: Wall  @: Agent  *: Path\n";
    std::cout << "Press any key to take a step\n\n";

    std::vector<HexNode*> visited;
    Display::PrintGrid(grid, start, target, start, visited);

    for (int i = 0; i < (int)path.size(); i++) {
        int ch = _getch();
        (void)ch;

        auto agent = path[i];

        if (i == 0)
            visited.push_back(start);
        else
            visited.push_back(path[i - 1]);

        Display::MoveCursorUp(grid.GetHeight());
        Display::PrintGrid(grid, start, target, agent, visited);
    }

    std::cout << "\nPath: (" << start->x_ << ", " << start->y_ << ")";
    for (auto node : path)
        std::cout << ", (" << node->x_ << ", " << node->y_ << ")";
    std::cout << "\nPath length: " << path.size() << "\n";
}