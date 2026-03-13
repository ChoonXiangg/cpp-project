#pragma once

#include <cmath>
#include <algorithm>
#include "NodeBase.h"

class HexNode : public NodeBase {
public:
    int x_, y_;

    HexNode(int x, int y) : x_(x), y_(y) {}

    double GetDistance(NodeBase* other) override {
        HexNode* o = static_cast<HexNode*>(other);

        // Convert offset coordinates (odd-r) to cube coordinates
        int q1 = x_ - (y_ - (y_ & 1)) / 2;
        int r1 = y_;
        int s1 = -q1 - r1;

        int q2 = o->x_ - (o->y_ - (o->y_ & 1)) / 2;
        int r2 = o->y_;
        int s2 = -q2 - r2;

        // Hex distance = max of absolute differences in cube coordinates
        // Parentheses around std::max prevent Windows max macro conflict
        int dq = std::abs(q1 - q2);
        int dr = std::abs(r1 - r2);
        int ds = std::abs(s1 - s2);
        return static_cast<double>((std::max)({ dq, dr, ds }));
    }
};