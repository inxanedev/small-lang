#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector<std::string> read_file(const char* filename) {
    std::vector<std::string> result;

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
        result.push_back(std::move(line));

    file.close();
    return result;
}

std::vector<std::string> split_string(const std::string& str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    
    std::string word;
    while (ss >> word)
        result.push_back(std::move(word));

    return result;
}
