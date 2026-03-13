#pragma once

#include <cmath>
#include "NodeBase.h"

class GridNode : public NodeBase {
public:
    int x_, y_;

    GridNode(int x, int y) : x_(x), y_(y) {}

    double GetDistance(NodeBase* other) override {
        GridNode* o = static_cast<GridNode*>(other);
        return std::abs(x_ - o->x_) + std::abs(y_ - o->y_);
    }
};