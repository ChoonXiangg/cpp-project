#pragma once

#include <vector>
#include <memory>
#include "SquareNode.h"
#include "Heuristic.h"

class SquareGrid {
public:
    SquareGrid(int width, int height, Heuristic heuristic = Heuristic::Manhattan);

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    SquareNode* GetNode(int x, int y) const { return nodes_[y * width_ + x].get(); }
    void SetWall(int x, int y);

private:
    int width_;
    int height_;
    std::vector<std::unique_ptr<SquareNode>> nodes_;
    void SetupNeighbors();
};