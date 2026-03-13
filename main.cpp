#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <memory>

#include "Complex.h"
#include "Constant.h"
#include "Operations.h"
#include "Variable.h"
#include "Context.h"
#include "Logger.h"
#include "Exceptions.h"


std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    bool hasDigit = false;
    size_t i = 0;

    if (s[0] == '+' || s[0] == '-') i = 1;
    for (; i < s.size(); ++i) {
        if (std::isdigit(static_cast<unsigned char>(s[i])) || s[i] == '.') {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return hasDigit;
}

bool isIdentifier(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isalpha(static_cast<unsigned char>(s[0])) && s[0] != '_')
        return false;
    for (size_t i = 1; i < s.size(); ++i) {
        if (!std::isalnum(static_cast<unsigned char>(s[i])) && s[i] != '_')
            return false;
    }
    return true;
}

// converts number -> constant, name -> variable
std::unique_ptr<Expression> parseAtom(const std::string& token) {
    if (isNumber(token)) {
        double value = std::stod(token);
        return std::make_unique<Constant>(value);
    }
    if (isIdentifier(token)) {
        return std::make_unique<Variable>(token);
    }
    throw ParseException("Invalid token: '" + token + "'");
}

std::unique_ptr<Expression> parseExpression(const std::string& input) {
    std::istringstream in(input);
    std::string leftTok;
    if (!(in >> leftTok)) {
        throw ParseException("Empty expression");
    }

    auto left = parseAtom(leftTok);

    char op;
    if (!(in >> op)) {
        // only one (number or variable)
        return left;
    }

    std::string rightTok;
    if (!(in >> rightTok)) {
        throw ParseException("Expected right operand after operator");
    }

    auto right = parseAtom(rightTok);

    switch (op) {
        case '+':
            return std::make_unique<AddOperation>(std::move(left), std::move(right));
        case '*':
            return std::make_unique<MulOperations>(std::move(left), std::move(right));
        case '/':
            return std::make_unique<DivOperations>(std::move(left), std::move(right));
        case '-':
            throw ParseException("Subtraction '-' is not supported in this version");
        default:
            throw ParseException(std::string("Unknown operator '") + op + "'");
    }
}

std::string complexToString(const Complex& c) {
    std::ostringstream oss;
    oss << c;
    return oss.str();
}

int main() {
    Logger logger("session.log");

    std::cout << ">>> Welcome to ComplexCalc (C++23)\n";
    std::cout << ">>> Type 'help' for commands, 'exit' to quit.\n\n";

    std::string line;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        std::string input = trim(line);
        if (input.empty()) continue;

        logger.write("Input: " + input);

        try {
            // exit commands
            if (input == "exit" || input == "quit") {
                break;
            }

            // help command
            if (input == "help") {
                std::cout << "Commands:\n"
                          << "  <expr>            Evaluate expression (e.g. 2 + 3, x * 4, 10 / 2)\n"
                          << "  let <name> = <value>   Set variable (real number)\n"
                          << "  get <name>        Get variable value\n"
                          << "  exit              Quit program\n";
                continue;
            }