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

    void deleteVariable(const std::string &name);

    std::optional<Complex> getVariable(const std::string &name) const;

    bool hasVariable(const std::string &name) const;
};

// Declare that such a variable exists somewhere in the program
// and we can use it where the this header file is included without creating a bunch of identical objects
extern Context globalContext;
