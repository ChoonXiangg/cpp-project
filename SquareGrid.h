#pragma once

#include <vector>
#include <memory>
#include "SquareNode.h"

class Grid {
public:
    Grid(int width, int height);

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    GridNode* GetNode(int x, int y) const { return nodes_[y * width_ + x].get(); }
    void SetWall(int x, int y);

private:
    int width_;
    int height_;
    std::vector<std::unique_ptr<GridNode>> nodes_;
    void SetupNeighbors();
};