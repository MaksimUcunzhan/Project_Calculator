#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include "Complex.h"

class Context {
private:
    std::unordered_map<std::string, Complex> variables;

public:
    void setVariable(const std::string &name, const Complex &value);

    std::optional<Complex> getVariable(const std::string &name) const;

    bool hasVariable(const std::string &name) const;

    void printAll(std::ostream& os) const {
        if (variables.empty()) {
            os << "  (none)\n";
            return;
        }
        for (const auto& [name, value] : variables) {
            os << "  " << name << " = " << value << "\n";
        }
    }
};

// Declare that such a variable exists somewhere in the program
// and we can use it where the this header file is included without creating a bunch of identical objects
extern Context globalContext;
