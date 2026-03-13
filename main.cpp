#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Display.h"
#include "runSquareGrid.h"
#include "runHexGrid.h"

int main() {
    Display::EnableAnsiEscapes();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int gridType;
    std::cout << "Grid type (1: Square, 2: Hex): ";
    std::cin >> gridType;

    int width, height;
    std::cout << "Grid width and height: ";
    std::cin >> width >> height;

    if (gridType == 1)
        runSquareGrid(width, height);
    else
        runHexGrid(width, height);

    return 0;
}