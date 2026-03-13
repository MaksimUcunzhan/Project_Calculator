#pragma once
#include <stdexcept>
#include <string>

// Basic exceptions for the project
class CalculatorException : public std::runtime_error {
public:
    explicit CalculatorException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// math exceptions group
class MathException : public CalculatorException {
public:
    explicit MathException(const std::string& msg)
        : CalculatorException(msg) {}
};

// exceptions division by zero (need for Complex)
class DivisionByZeroException : public MathException {
public:
    explicit DivisionByZeroException(const std::string& msg)
        : MathException("DivisionByZero: " + msg) {}
};

class NegativeSqrtException : public MathException {
public:
    explicit NegativeSqrtException(const std::string& msg)
        : MathException("NegativeSqrt: " + msg) {}
};

// parse exception
class ParseException : public CalculatorException {
public:
    explicit ParseException(const std::string& msg)
        : CalculatorException("ParseError: " + msg) {}
};

// variable exception group
class VariableException : public CalculatorException {
public:
    explicit VariableException(const std::string& msg)
        : CalculatorException(msg) {}
};

class UndefinedVariableException : public VariableException {
public:
    explicit UndefinedVariableException(const std::string& msg)
        : VariableException("UndefinedVariable: " + msg) {}
};

class VariableNameException : public VariableException {
public:
    explicit VariableNameException(const std::string& msg)
        : VariableException("InvalidName: " + msg) {}
};

// file exception
class FileIOException : public CalculatorException {
public:
    explicit FileIOException(const std::string& path)
        : CalculatorException("FileIO: Cannot access '" + path + "'") {}
};