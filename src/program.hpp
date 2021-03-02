#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

#include "utils.hpp"
#include "memory.hpp"
#include "label_storage.hpp"

class Program {
    public:
        Program(const char* filename) {
            std::vector<std::string> raw_code = read_file(filename);
            for (int i = 0; i < raw_code.size(); i++) {
                std::vector<std::string> split_line = split_string(raw_code[i]);
                if (split_line.at(0) == "LABEL")
                    m_labels.create_label(split_line.at(1), i + 1);
                code.push_back(std::move(split_line));
            }
        }
        void run() {
            Memory memory;
            std::unordered_map<std::string, int> labels;
            int ip = 0;
            while (ip != code.size()) {
                std::vector<std::string> instruction = code.at(ip);
                if (instruction.size() == 0) continue;
                if (instruction.at(0) == "print_text") {
                    expect_least_args(instruction, 1);
                    std::cout << build_line(instruction, 1);
                    std::cout.flush();
                } else if (instruction.at(0) == "newline") {
                    std::cout << std::endl;
                } else if (instruction.at(0) == "set") {
                    expect_least_args(instruction, 2);
                    memory.set_variable(instruction.at(1), parse_arg(instruction, 2));
                } else if (instruction.at(0) == "add") {
                    apply_binary_op(instruction, memory, Operation::ADD);
                } else if (instruction.at(0) == "sub") {
                    apply_binary_op(instruction, memory, Operation::SUB);
                } else if (instruction.at(0) == "mul") {
                    apply_binary_op(instruction, memory, Operation::MUL);
                } else if (instruction.at(0) == "div") {
                    apply_binary_op(instruction, memory, Operation::DIV);
                } else if (instruction.at(0) == "addv") {
                    apply_binary_op_v(instruction, memory, Operation::ADD);
                } else if (instruction.at(0) == "subv") {
                    apply_binary_op_v(instruction, memory, Operation::SUB);
                } else if (instruction.at(0) == "mulv") {
                    apply_binary_op_v(instruction, memory, Operation::MUL);
                } else if (instruction.at(0) == "divv") {
                    apply_binary_op_v(instruction, memory, Operation::DIV);
                } else if (instruction.at(0) == "print") {
                    expect_args(instruction, 1);
                    memory.print_var(instruction.at(1));
                    std::cout.flush();
                } else if (instruction.at(0) == "jump") {
                    expect_args(instruction, 1);
                    ip = m_labels.get_label(instruction.at(1)) - 1;
                    continue;
                } else if (instruction.at(0) == "jump_eqv") {
                    expect_args(instruction, 3);
                    if (memory.var_eq(instruction.at(2), instruction.at(3))) {
                        ip = m_labels.get_label(instruction.at(1)) - 1;
                        continue;
                    }
                } else if (instruction.at(0) == "jump_neqv") {
                    expect_args(instruction, 3);
                    if (!memory.var_eq(instruction.at(2), instruction.at(3))) {
                        ip = m_labels.get_label(instruction.at(1)) - 1;
                        continue;
                    }
                } else if (instruction.at(0) == "jump_eq") {
                    expect_args(instruction, 3);
                    std::variant<std::string, double> arg = parse_arg(instruction, 3);
                    auto var = memory.get_variable(instruction.at(2));
                    if (var.index() != arg.index())
                        error("Type mismatch at line " + std::to_string(ip + 1));
                    if (var.index() == 0) {
                        if (std::get<std::string>(var) == std::get<std::string>(arg)) {
                            ip = m_labels.get_label(instruction.at(1)) - 1;
                            continue;
                        }
                    } else {
                        if (std::get<double>(var) == std::get<double>(arg)) {
                            ip = m_labels.get_label(instruction.at(1)) - 1;
                            continue;
                        }
                    }
                } else if (instruction.at(0) == "jump_neq") {
                    expect_args(instruction, 3);
                    std::variant<std::string, double> arg = parse_arg(instruction, 3);
                    auto var = memory.get_variable(instruction.at(2));
                    if (var.index() != arg.index())
                        error("Type mismatch at line " + std::to_string(ip + 1));
                    if (var.index() == 0) {
                        if (std::get<std::string>(var) != std::get<std::string>(arg)) {
                            ip = m_labels.get_label(instruction.at(1)) - 1;
                            continue;
                        }
                    } else {
                        if (std::get<double>(var) != std::get<double>(arg)) {
                            ip = m_labels.get_label(instruction.at(1)) - 1;
                            continue;
                        }
                    }
                } else if (instruction.at(0) == "unset") {
                    expect_args(instruction, 1);
                    memory.unset(instruction.at(1));
                } else if (instruction.at(0) == "input_num") {
                    expect_args(instruction, 1);
                    double number;
                    std::cin >> number;
                    std::cin.ignore();
                    memory.set_variable(instruction.at(1), number);
                } else if (instruction.at(0) == "input_str") {
                    expect_args(instruction, 1);
                    std::string input;
                    std::getline(std::cin, input);
                    memory.set_variable(instruction.at(1), input);
                }

                
                ip += 1;
            }
        }
    private:
        std::vector<std::vector<std::string>> code;
        LabelStorage m_labels;
};
