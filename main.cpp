#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
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
    GridNode* agent,
    const std::vector<GridNode*>& visited)
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
            else if (std::find(visited.begin(), visited.end(), n) != visited.end())
                c = '*';
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

    // FindPath works with NodeBase* (generic), so we cast the result back to GridNode* since we know the concrete type
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
    // path[0] is now the first step after start, path.back() is target

    std::cout << "S: Start  E: End  .: Free  X: Wall  @: Agent  *: Path\n";
    std::cout << "Press any key to take a step\n\n";

    // Show initial state
    std::vector<GridNode*> visited;
    printGrid(nodes, start, target, start, visited);

    for (int i = 0; i < (int)path.size(); i++) {
        // Store the return value of _getch to fix C6031 warning
        int ch = _getch(); // wait for any keypress, no echo
        (void)ch; // explicitly ignore the value

        GridNode* agent = path[i];

        // Record the previous position as visited
        if (i == 0)
            visited.push_back(start);
        else
            visited.push_back(path[i - 1]);

        // Move cursor up HEIGHT lines to overwrite the previous grid
        std::cout << "\033[" << HEIGHT << "A";
        printGrid(nodes, start, target, agent, visited);
    }

    // Print the full path: start + path nodes
    std::cout << "\nPath: (" << start->x_ << ", " << start->y_ << ")";
    for (GridNode* node : path) {
        std::cout << ", (" << node->x_ << ", " << node->y_ << ")";
    }
    std::cout << "\nPath length: " << path.size() << "\n";

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            delete nodes[y][x];

    return 0;
}