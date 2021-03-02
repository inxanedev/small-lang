#include <iostream>
#include "utils.hpp"

int main() {
    auto result = split_string("");
    for (const std::string& word : result)
        std::cout << word << std::endl;
}
