#include "Operations.h"

BinaryOperation::BinaryOperation(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) : left(std::move(l)),
    right(std::move(r)) {
}

Complex BinaryOperation::evaluate() const {
    return applyOperations(left->evaluate(), right->evaluate());
}

std::string BinaryOperation::toString() const {
    return "(" + left->toString() + " " + getOperatorSymbol() +
           " " + right->toString() + ")";
}


Complex AddOperation::applyOperations(const Complex &l, const Complex &r) const {
    return l + r;
}

std::string AddOperation::getOperatorSymbol() const {
    return "+";
}

std::unique_ptr<Expression> AddOperation::clone() const {
    return std::make_unique<AddOperation>(left->clone(), right->clone());
}

Complex MulOperations::applyOperations(const Complex &l, const Complex &r) const {
    return l * r;
}

std::string MulOperations::getOperatorSymbol() const {
    return "*";
}

std::unique_ptr<Expression> MulOperations::clone() const {
    return std::make_unique<MulOperations>(left->clone(), right->clone());
}

Complex DivOperations::applyOperations(const Complex &l, const Complex &r) const {
    return l / r;
}

std::string DivOperations::getOperatorSymbol() const {
    return "/";
}

std::unique_ptr<Expression> DivOperations::clone() const {
    return std::make_unique<DivOperations>(left->clone(), right->clone());
}
