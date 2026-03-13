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

class AddOperation : public BinaryOperation {
public:
    //using the constructor of base class
    using BinaryOperation::BinaryOperation;

    Complex applyOperations(const Complex &l, const Complex &r) const override;

    std::string getOperatorSymbol() const override;

    std::unique_ptr<Expression> clone() const override;
};

class MulOperations : public BinaryOperation {
    using BinaryOperation::BinaryOperation;

    Complex applyOperations(const Complex &l, const Complex &r) const override;

    std::string getOperatorSymbol() const override;

    std::unique_ptr<Expression> clone() const override;
};

class DivOperations : public BinaryOperation {
    using BinaryOperation::BinaryOperation;

    Complex applyOperations(const Complex &l, const Complex &r) const override;

    std::string getOperatorSymbol() const override;

    std::unique_ptr<Expression> clone() const override;
};

class SubOperations : public BinaryOperation {
    using BinaryOperation::BinaryOperation;

    Complex applyOperations(const Complex &l, const Complex &r) const override;

    std::string getOperatorSymbol() const override;

    std::unique_ptr<Expression> clone() const override;
};
