#pragma once
#include <Context.h>
#include <Expression.h>
#include <string>
#include <memory>

class Variable : public Expression {
private:
    std::string name;

public:
    explicit Variable(const std::string &n);

    Complex evaluate() const override;

    std::string toString() const override;

    std::unique_ptr<Expression> clone() const override;
};
