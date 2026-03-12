#include "Context.h"

Context globalContext;

void Context::setVariable(const std::string &name, const Complex &value) {
    variables[name] = value;
}

std::optional<Complex> Context::getVariable(const std::string &name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return std::nullopt;
}
bool Context::hasVariable(const std::string &name) const {
    return variables.find(name) != variables.end();
}

