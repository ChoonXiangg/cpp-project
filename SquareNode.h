#pragma once

#include <cmath>
#include "NodeBase.h"

class SquareNode : public NodeBase {
public:
    int x_, y_;

    SquareNode(int x, int y) : x_(x), y_(y) {}

    double GetDistance(NodeBase* other) override {
        SquareNode* o = static_cast<SquareNode*>(other);
        return std::abs(x_ - o->x_) + std::abs(y_ - o->y_);
    }
};