#pragma once

#include <cmath>
#include <algorithm>
#include "NodeBase.h"

class HexNode : public NodeBase {
public:
    int x_, y_;

    HexNode(int x, int y) : x_(x), y_(y) {}

    double GetDistance(NodeBase* other) override {
        auto o = static_cast<HexNode*>(other);

        if (GetHeuristic() == Heuristic::Euclidean) {
            // Convert hex offset to approximate pixel position for Euclidean distance
            double px1 = x_ + (y_ % 2 == 1 ? 0.5 : 0.0);
            double py1 = y_ * 0.866;  // sqrt(3)/2 for hex row spacing
            double px2 = o->x_ + (o->y_ % 2 == 1 ? 0.5 : 0.0);
            double py2 = o->y_ * 0.866;
            double dx = px1 - px2;
            double dy = py1 - py2;
            return std::sqrt(dx * dx + dy * dy);
        }

        // Cube distance (default)
        int q1 = x_ - (y_ - (y_ & 1)) / 2;
        int r1 = y_;
        int s1 = -q1 - r1;

        int q2 = o->x_ - (o->y_ - (o->y_ & 1)) / 2;
        int r2 = o->y_;
        int s2 = -q2 - r2;

        int dq = std::abs(q1 - q2);
        int dr = std::abs(r1 - r2);
        int ds = std::abs(s1 - s2);
        return static_cast<double>((std::max)({ dq, dr, ds }));
    }
};