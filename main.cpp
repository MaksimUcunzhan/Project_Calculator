#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "Complex.h"
#include "Constant.h"
#include "Operations.h"
#include "Variable.h"
#include "Context.h"
#include "Logger.h"
#include "Exceptions.h"
#include "Parser.h"


std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
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

std::string complexToString(const Complex& c) {
    std::ostringstream oss;
    oss << c;
    return oss.str();
}

int main() {
    Logger logger("session.log");

    std::cout << ">>> Welcome to Complex Calculator\n";
    std::cout << ">>> Type 'help' for commands, 'exit' to quit.\n\n";

    std::string line;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;

        std::string input = trim(line);
        if (input.empty()) continue;

        logger.write("Input: " + input);

        try {
            if (input == "exit" || input == "quit")
                break;

            if (input == "help") {
                std::cout << "\nAvailable commands:\n"
                          << "  <expression>          Calculate expression\n"
                          << "  let <name> = <expr>   Assign variable\n"
                          << "  get <name>            Get variable value\n"
                          << "  vars                  List all variables\n"
                          << "  clear <name>          Remove variable\n"
                          << "  help                  Show this help\n"
                          << "  exit                  Exit program\n\n";
                continue;
            }

            if (input == "vars") {
                std::cout << "Defined variables:\n";
                globalContext.printAll(std::cout);
                std::cout << "\n";
                continue;
            }

            // let command
            if (input.rfind("let ", 0) == 0) {
                size_t eqPos = input.find('=');
                if (eqPos == std::string::npos)
                    throw ParseException("Invalid assignment, expected '='");

                std::string namePart  = trim(input.substr(4, eqPos - 4));
                std::string valuePart = trim(input.substr(eqPos + 1));

                if (!isIdentifier(namePart))
                    throw VariableNameException("Invalid variable name: '" + namePart + "'");

                Parser parser(valuePart);
                auto expr = parser.parse();
                Complex value = expr->evaluate();

                globalContext.setVariable(namePart, value);
                std::cout << "[INFO] Variable '" << namePart << "' = " << value << "\n";
                logger.write("Set " + namePart + " = " + complexToString(value));
                continue;
            }

            // get command
            if (input.rfind("get ", 0) == 0) {
                std::string name = trim(input.substr(4));
                if (!isIdentifier(name))
                    throw VariableNameException("Invalid variable name: '" + name + "'");

                auto val = globalContext.getVariable(name);
                if (!val.has_value())
                    throw UndefinedVariableException("Variable '" + name + "' not found");

                std::cout << "= " << val.value() << "\n";
                logger.write("Get " + name + " = " + complexToString(val.value()));
                continue;
            }

            // clear function
            if (input.rfind("clear ", 0) == 0) {
                std::string name = trim(input.substr(6));
                if (!isIdentifier(name))
                    throw VariableNameException("Invalid variable name: '" + name + "'");

                if (!globalContext.hasVariable(name))
                    throw UndefinedVariableException("Not found variable: '" + name + "'");

                globalContext.deleteVariable(name);
                std::cout << "[INFO] Variable '" << name << "' deleted\n";
                logger.write("Deleted " + name);
                continue;
            }

            // Parse expression
            Parser parser(input);
            auto expr = parser.parse();
            Complex result = expr->evaluate();

            std::cout << "= " << result << "\n";
            logger.write("Result: " + complexToString(result));
        }
        catch (const DivisionByZeroException& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            logger.write(std::string("ERROR: ") + e.what());
        }
        catch (const UndefinedVariableException& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            logger.write(std::string("ERROR: ") + e.what());
        }
        catch (const VariableNameException& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            logger.write(std::string("ERROR: ") + e.what());
        }
        catch (const ParseException& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            logger.write(std::string("ERROR: ") + e.what());
        }
        catch (const CalculatorException& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            logger.write(std::string("ERROR: ") + e.what());
        }
        catch (const std::exception& e) {
            std::cerr << "[ERROR] Unexpected: " << e.what() << "\n";
            logger.write(std::string("ERROR: Unexpected: ") + e.what());
        }
    }

    std::cout << ">>> Goodbye!\n";
    return 0;
}