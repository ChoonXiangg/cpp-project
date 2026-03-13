#pragma once

#include <iostream>
#include <string>
#include <functional>

namespace Input {
    // Read an int, re-prompting until valid
    int ReadInt(const std::string& prompt);

    // Read an int that must pass a validation check, re-prompting until valid
    int ReadInt(const std::string& prompt, std::function<bool(int)> validate, const std::string& errorMsg);

    // Read x and y coordinates within grid bounds
    void ReadPosition(const std::string& prompt, int& x, int& y, int width, int height);
}