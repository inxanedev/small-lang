#include <iostream>
#include "utils.hpp"
#include "error.hpp"
#include "program.hpp"

int main(int argc, char** argv) {
    if (argc < 2)
       error("Please supply filename to the interpreter!");

    Program program(argv[1]);
    program.run();
}
