#pragma once

#include <unordered_map>
#include <string>

#include "error.hpp"

class LabelStorage {
    public:
        void create_label(const std::string& label, int line_number) {
            if (label_exists(label)) return;
            labels.insert_or_assign(label, line_number);
        }

        bool label_exists(const std::string& label) {
            return labels.find(label) != labels.end();
        }

        int get_label(const std::string& label) {
            if (!label_exists(label))
                error("Label " + label + " doesn't exist!");
            return labels.at(label);
        }
    private:
        std::unordered_map<std::string, int> labels;
};
