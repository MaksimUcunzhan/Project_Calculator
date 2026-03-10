//
// Created by Максим Учунжян on 09.03.2026.
//

#ifndef PROJECT_CALCULATOR_COMPLEX_H
#define PROJECT_CALCULATOR_COMPLEX_H

#endif //PROJECT_CALCULATOR_COMPLEX_H

#pragma once
#include <iostream>

class Complex {
private:
    double real_;
    double imag_;

public:
    // constructors
    constexpr Complex(double r = 0.0, double i = 0.0) : real_(r), imag_(i) {}

    // getters (constexpr for compile-time calculations)
    constexpr double real() const { return real_; }
    constexpr double imag() const { return imag_; }

    // overload
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // comparison
    bool operator==(const Complex& other) const;

    // output to stream
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    // abs
    double modulus() const;
};

// constexpr constants
namespace MathConst {
    constexpr double PI = 3.14159265358979323846;
    constexpr double E = 2.71828182845904523536;
    constexpr Complex I(0.0, 1.0);  // Imaginary unit
}

