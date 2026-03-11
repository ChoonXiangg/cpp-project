#pragma once

#include <vector>
#include "GridNode.h"

class Grid {
public:
    static const int WIDTH = 5;
    static const int HEIGHT = 5;

    Grid(int layout[HEIGHT][WIDTH]);
    ~Grid();

    GridNode* GetNode(int x, int y) const { return nodes_[y][x]; }

private:
    GridNode* nodes_[HEIGHT][WIDTH];
    void SetupNeighbors();
};