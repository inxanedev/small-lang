#pragma once
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> read_file(const char* filename) {
    std::vector<std::string> result;

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
        result.push_back(std::move(line));

    file.close();
    return result;
}
