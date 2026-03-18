#include <iostream>
#include <algorithm>
#include <windows.h>
#include "Display.h"

void Display::EnableAnsiEscapes() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// Helper to determine cell character based on state and weight
static char GetCellChar(NodeBase* n, NodeBase* start, NodeBase* target,
    NodeBase* agent, bool isVisited)
{
    if (n == agent && n != start && n != target)
        return '@';
    if (n == start)
        return 'S';
    if (n == target)
        return 'E';
    if (!n->IsWalkable())
        return 'X';
    if (isVisited)
        return '*';
    // Show weight as digit for weighted cells (2-9), '.' for default (1)
    auto weight = static_cast<int>(n->GetWeight());
    if (weight >= 2 && weight <= 9)
        return '0' + weight;
    return '.';
}

void Display::PrintGrid(const SquareGrid& grid,
    SquareNode* start, SquareNode* target,
    SquareNode* agent,
    const std::vector<SquareNode*>& visited)
{
    auto width = grid.GetWidth();
    auto height = grid.GetHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto n = grid.GetNode(x, y);
            bool isVisited = std::any_of(visited.begin(), visited.end(),
                [n](SquareNode* v) { return v == n; });

            std::cout << GetCellChar(n, start, target, agent, isVisited);
            if (x < width - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Display::PrintGrid(const HexGrid& grid,
    HexNode* start, HexNode* target,
    HexNode* agent,
    const std::vector<HexNode*>& visited)
{
    auto width = grid.GetWidth();
    auto height = grid.GetHeight();

    for (int y = 0; y < height; y++) {
        if (y % 2 == 1)
            std::cout << ' ';

        for (int x = 0; x < width; x++) {
            auto n = grid.GetNode(x, y);
            bool isVisited = std::any_of(visited.begin(), visited.end(),
                [n](HexNode* v) { return v == n; });

            std::cout << GetCellChar(n, start, target, agent, isVisited);
            if (x < width - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Display::MoveCursorUp(int lines) {
    std::cout << "\033[" << lines << "A";
}