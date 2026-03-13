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