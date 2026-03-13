#include "HexGrid.h"

HexGrid::HexGrid(int width, int height, Heuristic heuristic)
    : width_(width), height_(height) {
    nodes_.reserve(width * height);
    for (int y = 0; y < height_; y++)
        for (int x = 0; x < width_; x++) {
            auto node = std::make_unique<HexNode>(x, y);
            node->SetHeuristic(heuristic);
            nodes_.push_back(std::move(node));
        }

    SetupNeighbors();
}

void HexGrid::SetWall(int x, int y) {
    GetNode(x, y)->SetWalkable(false);
}

void HexGrid::SetupNeighbors() {
    int evenDx[] = { -1, 1,  0, -1,  0, -1 };
    int evenDy[] = { 0, 0, -1, -1,  1,  1 };
    int oddDx[] = { -1, 1,  0,  1,  0,  1 };
    int oddDy[] = { 0, 0, -1, -1,  1,  1 };

    for (int y = 0; y < height_; y++) {
        int* dx = (y % 2 == 0) ? evenDx : oddDx;
        int* dy = (y % 2 == 0) ? evenDy : oddDy;

        for (int x = 0; x < width_; x++) {
            std::vector<NodeBase*> neighbors;
            for (int d = 0; d < 6; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < width_ && ny >= 0 && ny < height_)
                    neighbors.push_back(GetNode(nx, ny));
            }
            GetNode(x, y)->SetNeighbors(neighbors);
        }
    }
}