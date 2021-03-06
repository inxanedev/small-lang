#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <variant>

#include "error.hpp"
#include "memory.hpp"

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

void expect_args(const std::vector<std::string>& instruction, int instruction_amount) {
    if (instruction.size() - 1 != instruction_amount)
        error("Instruction " + instruction.at(0) + " expects " + std::to_string(instruction_amount) + " arguments, but got " + std::to_string(instruction.size() - 1));
}

void expect_least_args(const std::vector<std::string>& instruction, int instruction_amount) {
    if (instruction.size() - 1 < instruction_amount)
        error("Instruction " + instruction.at(0) + " expects at least " + std::to_string(instruction_amount) + " arguments, but got only " + std::to_string(instruction.size() - 1));
}

std::string build_line(const std::vector<std::string>& split_line, int start_index) {
    std::ostringstream ss;
    for (int i = start_index; i < split_line.size(); i++)
        ss << split_line.at(i) << (i != split_line.size() - 1 ? " " : "");

    return ss.str();
}

std::variant<std::string, double> parse_arg(const std::vector<std::string>& instruction, int start_index) {
    if (instruction.size() > start_index + 1)
        return build_line(instruction, start_index);
    char* p;
    double temp = strtod(instruction.at(start_index).c_str(), &p);
    if (*p == 0)
        return temp;
    else
        return instruction.at(start_index);
}

double parse_as_double(const std::string& str) {
    char* p;
    double temp = strtod(str.c_str(), &p);
    if (*p == 0)
        return temp;
    error("Couldn't parse string " + str + " as double!");
    return -1;
}

enum class Operation {
    ADD, SUB, MUL, DIV
};

void apply_binary_op(const std::vector<std::string>& instruction, Memory& memory, Operation op) {
    expect_args(instruction, 2);
    memory.type_check<double>(instruction.at(1));
    
    double temp = memory.get_double(instruction.at(1));
    double argument = parse_as_double(instruction.at(2));
    switch (op) {
        case Operation::ADD:
            temp += argument;
            break;
        case Operation::SUB:
            temp -= argument;
            break;
        case Operation::MUL:
            temp *= argument;
            break;
        case Operation::DIV:
            temp /= argument;
            break;
    }
    memory.set_variable(instruction.at(1), temp);
}

void apply_binary_op_v(const std::vector<std::string>& instruction, Memory& memory, Operation op) {
    expect_args(instruction, 2);
    memory.type_check<double>(instruction.at(1)); memory.type_check<double>(instruction.at(2));

    double a = memory.get_double(instruction.at(1));
    double b = memory.get_double(instruction.at(2));

    switch (op) {
        case Operation::ADD:
            a += b;
            break;
        case Operation::SUB:
            a -= b;
            break;
        case Operation::MUL:
            a *= b;
            break;
        case Operation::DIV:
            a /= b;
            break;
    }

    memory.set_variable(instruction.at(1), a);
}

std::string parse_as_string(const std::variant<std::string, double>& variable) {
    if (variable.index() == 0) return std::get<std::string>(variable);
                          else return std::to_string(std::get<double>(variable));
}
