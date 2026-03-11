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

void Display::PrintGrid(const Grid& grid,
    GridNode* start, GridNode* target,
    GridNode* agent,
    const std::vector<GridNode*>& visited)
{
    for (int y = 0; y < Grid::HEIGHT; y++) {
        for (int x = 0; x < Grid::WIDTH; x++) {
            GridNode* n = grid.GetNode(x, y);
            char c;
            if (n == agent && n != start && n != target)
                c = '@';
            else if (n == start)
                c = 'S';
            else if (n == target)
                c = 'E';
            else if (!n->IsWalkable())
                c = 'X';
            else if (std::find(visited.begin(), visited.end(), n) != visited.end())
                c = '*';
            else
                c = '.';

            std::cout << c;
            if (x < Grid::WIDTH - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Display::MoveCursorUp(int lines) {
    std::cout << "\033[" << lines << "A";
}