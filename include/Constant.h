//
// Created by Максим Учунжян on 11.03.2026.
//

#ifndef PROJECT_CALCULATOR_CONSTANT_H
#define PROJECT_CALCULATOR_CONSTANT_H

#endif //PROJECT_CALCULATOR_CONSTANT_H

#pragma once
#include "Expression.h"
#include "Complex.h"
#include <string>
#include <memory>

class Constant : public Expression {
private:
    Complex value_;

public:
    constexpr Constant(const Complex& val) : value_(val) {}

    constexpr Constant(double real, double imag = 0.0)
        : value_(real, imag) {}

    constexpr Complex evaluate() const override {
        return value_;
    }

    std::string toString() const override {
        std::string result = std::to_string(value_.real());
        if (value_.imag() != 0) {
            result += (value_.imag() > 0 ? "+" : "");
            result += std::to_string(value_.imag()) + "i";
        }
        return result;
    }

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<Constant>(value_);
    }
};

namespace MathConst {
    constexpr Constant PI(3.14159265358979323846, 0.0);
    constexpr Constant E(2.71828182845904523536, 0.0);
    constexpr Constant I(0.0, 1.0);  // Мнимая единица
}
