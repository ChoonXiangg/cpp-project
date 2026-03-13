#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include "SquareGrid.h"
#include "SquareNode.h"
#include "Display.h"
#include "Pathfinding.h"
#include "Input.h"
#include "runSquareGrid.h"

void runSquareGrid(int width, int height, Heuristic heuristic) {
    SquareGrid grid(width, height, heuristic);

    int sx, sy, ex, ey;
    Input::ReadPosition("Start position (x y): ", sx, sy, width, height);
    Input::ReadPosition("End position (x y): ", ex, ey, width, height);

    auto start = grid.GetNode(sx, sy);
    auto target = grid.GetNode(ex, ey);

    int maxWalls = width * height - 2;
    auto wallCount = Input::ReadInt("Number of walls: ",
        [maxWalls](int v) { return v >= 0 && v <= maxWalls; },
        "Must be between 0 and " + std::to_string(maxWalls) + ".");

    if (wallCount > 0) {
        auto choice = Input::ReadInt("Wall placement (1: Manual, 2: Random): ",
            [](int v) { return v == 1 || v == 2; },
            "Please enter 1 or 2.");

        if (choice == 1) {
            for (int i = 0; i < wallCount; i++) {
                int wx, wy;
                while (true) {
                    Input::ReadPosition("Wall " + std::to_string(i + 1) + " position (x y): ",
                        wx, wy, width, height);
                    auto node = grid.GetNode(wx, wy);
                    if (node == start || node == target)
                        std::cout << "Cannot place a wall on start or end.\n";
                    else if (!node->IsWalkable())
                        std::cout << "Wall already exists at (" << wx << ", " << wy << ").\n";
                    else
                        break;
                }
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
    }

    auto basePath = Pathfinding::FindPath(start, target);

    if (basePath.empty()) {
        std::cout << "\n";
        std::vector<SquareNode*> empty;
        Display::PrintGrid(grid, start, target, start, empty);
        std::cout << "\nNo path found.\n";
        return;
    }

    std::vector<SquareNode*> path(basePath.size());
    std::transform(basePath.begin(), basePath.end(), path.begin(),
        [](NodeBase* node) { return static_cast<SquareNode*>(node); });
    std::reverse(path.begin(), path.end());

    std::cout << "\nS: Start  E: End  .: Free  X: Wall  @: Agent  *: Path\n";
    std::cout << "Press any key to take a step\n\n";

    std::vector<SquareNode*> visited;
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