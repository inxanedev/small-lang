#pragma once

#include <unordered_map>
#include <variant>
#include <string>
#include "error.hpp"

class Memory {
    using variable_t = std::variant<std::string, double>;
    public:
        std::variant<std::string, double>& get_variable(const std::string& var_name) {
            var_check(var_name);
            return m_memory.at(var_name);
        }
        
        double get_double(const std::string& var_name) {
            type_check<double>(var_name);
            
            return std::get<double>(get_variable(var_name));
        }

        std::string get_string(const std::string& var_name) {
            var_check(var_name); type_check<std::string>(var_name);
            
            return std::get<std::string>(get_variable(var_name));
        }

        void set_variable(const std::string& var_name, variable_t value) {
            m_memory.insert_or_assign(var_name, value);
        }

        void var_check(const std::string& var_name) {
            if (m_memory.find(var_name) == m_memory.end())
                error("Variable " + var_name + " not initialized!");
        }

        void type_check(const std::string& a, const std::string& b) {
            if (get_variable(a).index() != get_variable(b).index())
                error("Variables " + a + " and " + b + " have mismatching types!");
        }

        template <typename T>
        void type_check(const std::string& var_name) {
            if (!std::holds_alternative<T>(get_variable(var_name))) {
                if (std::is_same_v<T, double>) {
                    error("Variable " + var_name + " was expected to be type double!");
                } else if (std::is_same_v<T, std::string>) {
                    error("Variable " + var_name + " was expected to be type string!");
                }
            }
        }

        bool var_eq(const std::string& a, const std::string& b) {
            type_check(a, b);

            variable_t left = get_variable(a);
            variable_t right = get_variable(b);
            if (left.index() == 1)
                return std::get<double>(left) == std::get<double>(right);
            else
                return std::get<std::string>(left) == std::get<std::string>(right);
        }

        void print_var(const std::string& var_name) {
            variable_t value = get_variable(var_name);
            if (value.index() == 0)
                std::cout << std::get<std::string>(value);
            else
                printf("%g", std::get<double>(value));
        }

        void unset(const std::string& var_name) {
            var_check(var_name);
            m_memory.erase(var_name);
        }
    private:
        std::unordered_map<std::string, variable_t> m_memory;
        std::unordered_map<std::string, int> m_labels;
};
