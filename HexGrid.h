#pragma once

#include <vector>
#include <memory>
#include "HexNode.h"
#include "Heuristic.h"

class HexGrid {
public:
    HexGrid(int width, int height, Heuristic heuristic = Heuristic::Manhattan);

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    HexNode* GetNode(int x, int y) const { return nodes_[y * width_ + x].get(); }
    void SetWall(int x, int y);
    void SetWeight(int x, int y, double weight);

private:
    int width_;
    int height_;
    std::vector<std::unique_ptr<HexNode>> nodes_;
    void SetupNeighbors();
};