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