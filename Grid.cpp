#include "Grid.h"

Grid::Grid(int width, int height) : width_(width), height_(height) {
    nodes_.resize(width * height);
    for (int y = 0; y < height_; y++)
        for (int x = 0; x < width_; x++)
            nodes_[y * width_ + x] = new GridNode(x, y);

    SetupNeighbors();
}

Grid::~Grid() {
    for (GridNode* node : nodes_)
        delete node;
}

void Grid::SetWall(int x, int y) {
    GetNode(x, y)->SetWalkable(false);
}

void Grid::SetupNeighbors() {
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            std::vector<NodeBase*> neighbors;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < width_ && ny >= 0 && ny < height_)
                    neighbors.push_back(GetNode(nx, ny));
            }
            GetNode(x, y)->SetNeighbors(neighbors);
        }
    }
}