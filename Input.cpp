#include "Input.h"
#include <limits>

int Input::ReadInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value)
            return value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
    }
}

int Input::ReadInt(const std::string& prompt, std::function<bool(int)> validate, const std::string& errorMsg) {
    while (true) {
        int value = ReadInt(prompt);
        if (validate(value))
            return value;
        std::cout << errorMsg << "\n";
    }
}

void Input::ReadPosition(const std::string& prompt, int& x, int& y, int width, int height) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> x >> y) {
            if (x >= 0 && x < width && y >= 0 && y < height)
                return;
            std::cout << "Position out of bounds. Valid range: x(0-" << width - 1
                << "), y(0-" << height - 1 << ").\n";
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter two numbers.\n";
        }
    }
}