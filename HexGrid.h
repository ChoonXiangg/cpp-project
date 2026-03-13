#pragma once

#include <vector>
#include <memory>
#include "HexNode.h"

class HexGrid {
public:
    HexGrid(int width, int height);

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    HexNode* GetNode(int x, int y) const { return nodes_[y * width_ + x].get(); }
    void SetWall(int x, int y);

private:
    int width_;
    int height_;
    std::vector<std::unique_ptr<HexNode>> nodes_;
    void SetupNeighbors();
};