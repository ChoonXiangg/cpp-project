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
            char c;
            if (n == agent && n != start && n != target)
                c = '@';
            else if (n == start)
                c = 'S';
            else if (n == target)
                c = 'E';
            else if (!n->IsWalkable())
                c = 'X';
            else if (std::any_of(visited.begin(), visited.end(),
                [n](SquareNode* v) { return v == n; }))
                c = '*';
            else
                c = '.';

            std::cout << c;
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
        // Indent odd rows by one space for the staggered hex look
        if (y % 2 == 1)
            std::cout << ' ';

        for (int x = 0; x < width; x++) {
            auto n = grid.GetNode(x, y);
            char c;
            if (n == agent && n != start && n != target)
                c = '@';
            else if (n == start)
                c = 'S';
            else if (n == target)
                c = 'E';
            else if (!n->IsWalkable())
                c = 'X';
            else if (std::any_of(visited.begin(), visited.end(),
                [n](HexNode* v) { return v == n; }))
                c = '*';
            else
                c = '.';

            std::cout << c;
            if (x < width - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Display::MoveCursorUp(int lines) {
    std::cout << "\033[" << lines << "A";
}