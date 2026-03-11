#include "Grid.h"

Grid::Grid(int layout[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
            nodes_[y][x] = new GridNode(x, y);
            nodes_[y][x]->SetWalkable(layout[y][x] == 0);
        }

    SetupNeighbors();
}

Grid::~Grid() {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            delete nodes_[y][x];
}

void Grid::SetupNeighbors() {
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::vector<NodeBase*> neighbors;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
                    neighbors.push_back(nodes_[ny][nx]);
            }
            nodes_[y][x]->SetNeighbors(neighbors);
        }
    }
}