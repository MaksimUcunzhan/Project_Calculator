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
    BinaryOperation(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r);

    virtual ~BinaryOperation() = default;


    virtual Complex applyOperations(const Complex &l, const Complex &r) const = 0;

    virtual std::string getOperatorSymbol() const = 0;

    Complex evaluate() const override;

    std::string toString() const override;
};
