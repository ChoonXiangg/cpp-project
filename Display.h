#pragma once

#include <vector>
#include "SquareGrid.h"
#include "SquareNode.h"

namespace Display {
    void EnableAnsiEscapes();
    void PrintGrid(const Grid& grid,
        GridNode* start, GridNode* target,
        GridNode* agent,
        const std::vector<GridNode*>& visited);
    void MoveCursorUp(int lines);
}