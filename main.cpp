#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Display.h"
#include "Input.h"
#include "runSquareGrid.h"
#include "runHexGrid.h"

int main() {
    Display::EnableAnsiEscapes();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    auto gridType = Input::ReadInt("Grid type (1: Square, 2: Hex): ",
        [](int v) { return v == 1 || v == 2; },
        "Please enter 1 or 2.");

    auto width = Input::ReadInt("Grid width: ",
        [](int v) { return v >= 2; },
        "Width must be at least 2.");

    auto height = Input::ReadInt("Grid height: ",
        [](int v) { return v >= 2; },
        "Height must be at least 2.");

    if (gridType == 1)
        runSquareGrid(width, height);
    else
        runHexGrid(width, height);

    return 0;
}