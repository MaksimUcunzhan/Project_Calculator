#pragma once
#include <memory>
#include <string>
#include "Expression.h"

// created a base class for binary operations
class BinaryOperation : public Expression {
protected:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    // created a constructor
    BinaryOperation(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) : left(std::move(l)), right(std::move(r)) {
    }
    virtual Complex applyOperations(const Complex& l,const Complex& r) const = 0;
    virtual std::string getOperatorSymbol() const = 0;

    Complex evaluate() const override {
        return applyOperations(left->evaluate(),right->evaluate());
    }
    std::string toString() const override {
        return "(" + left->toString() + " " + getOperatorSymbol() +
               " " + right->toString() + ")";
    }


};
