#include <iostream>
#include "utils.hpp"

int main() {
    auto contents = read_file("file.txt");
    for (const std::string& line : contents)
        std::cout << line << std::endl;
}
