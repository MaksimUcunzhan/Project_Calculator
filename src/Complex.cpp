//
// Created by Максим Учунжян on 09.03.2026.
//

#include "Complex.h"
#include "Exceptions.h"

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(
        real_ * other.real_ - imag_ * other.imag_,
        real_ * other.imag_ + imag_ * other.real_
    );
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denom == 0.0) {
        throw DivisionByZeroException("Division by zero complex number");
    }
    return Complex(
        (real_ * other.real_ + imag_ * other.imag_) / denom,
        (imag_ * other.real_ - real_ * other.imag_) / denom
    );
}

bool Complex::operator==(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    if (c.imag_ >= 0) {
        os << c.real_ << "+" << c.imag_ << "i";
    } else {
        os << c.real_ << c.imag_ << "i";
    }
    return os;
}

double Complex::modulus() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}
