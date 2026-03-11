#pragma once

#include <vector>
#include "Grid.h"
#include "GridNode.h"

namespace Display {
    void EnableAnsiEscapes();
    void PrintGrid(const Grid& grid,
        GridNode* start, GridNode* target,
        GridNode* agent,
        const std::vector<GridNode*>& visited);
    void MoveCursorUp(int lines);
}