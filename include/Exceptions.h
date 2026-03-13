//
// Created by Максим Учунжян on 10.03.2026.
//

#ifndef PROJECT_CALCULATOR_EXCEPTIONS_H
#define PROJECT_CALCULATOR_EXCEPTIONS_H

#endif //PROJECT_CALCULATOR_EXCEPTIONS_H

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
