#pragma once

#include <vector>
#include "GridNode.h"

class Grid {
public:
    Grid(int width, int height);
    ~Grid();

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    GridNode* GetNode(int x, int y) const { return nodes_[y * width_ + x]; }
    void SetWall(int x, int y);

private:
    int width_;
    int height_;
    std::vector<GridNode*> nodes_;
    void SetupNeighbors();
};