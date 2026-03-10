//
// Created by Максим Учунжян on 09.03.2026.
//

#ifndef PROJECT_CALCULATOR_EXPRESSION_H
#define PROJECT_CALCULATOR_EXPRESSION_H

#endif //PROJECT_CALCULATOR_EXPRESSION_H

#pragma once
#include <memory>
#include <string>
#include "Complex.h"

// abstract base class
class Expression {
public:
    // virtual destructor
    virtual ~Expression() = default;

    // calculating value
    virtual Complex evaluate() const = 0;

    // string
    virtual std::string toString() const = 0;

    // Clonability (for copy tree)
    virtual std::unique_ptr<Expression> clone() const = 0;
};