#include <iostream>
#include <vector>
#include <algorithm>
#include "GridNode.h"
#include "Pathfinding.h"

const int WIDTH = 5;
const int HEIGHT = 5;

int layout[HEIGHT][WIDTH] = {
    { 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 },
};

void printGrid(GridNode* nodes[HEIGHT][WIDTH],
    GridNode* start, GridNode* target,
    GridNode* agent)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            GridNode* n = nodes[y][x];
            char c;
            if (n == agent && n != start && n != target)
                c = '@';
            else if (n == start)
                c = 'S';
            else if (n == target)
                c = 'E';
            else if (!n->IsWalkable())
                c = 'X';
            else
                c = '.';

            std::cout << c;
            if (x < WIDTH - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    GridNode* nodes[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
            nodes[y][x] = new GridNode(x, y);
            nodes[y][x]->SetWalkable(layout[y][x] == 0);
        }

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::vector<NodeBase*> neighbors;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
                    neighbors.push_back(nodes[ny][nx]);
            }
            nodes[y][x]->SetNeighbors(neighbors);
        }
    }

    GridNode* start = nodes[0][0];
    GridNode* target = nodes[4][4];

    std::vector<NodeBase*> path = Pathfinding::FindPath(start, target);

    if (path.empty()) {
        std::cout << "No path found.\n";
        return 0;
    }

    // FindPath returns path in reverse (target -> start), so reverse it
    std::reverse(path.begin(), path.end());
    // path[0] is now the first step after start, path.back() is target

    std::cout << "S: Start  E: End  .: Free  X: Wall  @: Agent\n";
    std::cout << "Press Enter to step...\n\n";

    // Show initial state
    printGrid(nodes, start, target, start);

    for (int i = 0; i < (int)path.size(); i++) {
        std::cin.get(); // wait for Enter
        GridNode* agent = static_cast<GridNode*>(path[i]);
        std::cout << '\n';
        printGrid(nodes, start, target, agent);
    }

    std::cout << "\nReached the end!\n";

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            delete nodes[y][x];

    return 0;
}