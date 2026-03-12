#include "Operations.h"

BinaryOperation::BinaryOperation(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) : left(std::move(l)),
    right(std::move(r)) {
}
Complex BinaryOperation::evaluate() const {
    return applyOperations(left->evaluate(),right->evaluate());
}
std::string BinaryOperation::toString() const {
    return "(" + left->toString() + " " + getOperatorSymbol() +
           " " + right->toString() + ")";
}


