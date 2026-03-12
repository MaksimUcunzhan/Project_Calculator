#include "Variable.h"
#include <stdexcept>

class UndefinedVariableException : public std::runtime_error {
public:
    explicit UndefinedVariableException(const std::string &msg) : std::runtime_error(msg) {
    }
};

Variable::Variable(const std::string &n) : name(n) {
}

Complex Variable::evaluate() const {
    auto value = globalContext.getVariable(name);
    if (!value.has_value()) {
        throw UndefinedVariableException("Variable '" + name + "' is not defined");
    }
    return value.value();
}

std::string Variable::toString() const {
    return name;
}

std::unique_ptr<Expression> Variable::clone() const {
    return std::make_unique<Variable>(name);
}


