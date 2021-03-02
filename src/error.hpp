#pragma once

#include <iostream>

void error(const std::string& reason) {
    std::cout << std::endl << "ERROR: " << reason << std::endl;
    std::exit(1);
}
