#pragma once

#include <vector>
#include "SquareGrid.h"
#include "SquareNode.h"
#include "HexGrid.h"
#include "HexNode.h"

namespace Display {
    void EnableAnsiEscapes();

    void PrintGrid(const Grid& grid,
        GridNode* start, GridNode* target,
        GridNode* agent,
        const std::vector<GridNode*>& visited);

    void PrintGrid(const HexGrid& grid,
        HexNode* start, HexNode* target,
        HexNode* agent,
        const std::vector<HexNode*>& visited);

    void MoveCursorUp(int lines);
}