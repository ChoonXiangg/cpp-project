#pragma once

#include <cmath>
#include "NodeBase.h"

class SquareNode : public NodeBase {
public:
    int x_, y_;

    SquareNode(int x, int y) : x_(x), y_(y) {}

    double GetDistance(NodeBase* other) override {
        auto o = static_cast<SquareNode*>(other);
        int dx = x_ - o->x_;
        int dy = y_ - o->y_;

        if (GetHeuristic() == Heuristic::Euclidean)
            return std::sqrt(dx * dx + dy * dy);

        // Manhattan (default)
        return std::abs(dx) + std::abs(dy);
    }
};