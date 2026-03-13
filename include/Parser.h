#pragma once
#include <string>
#include <memory>
#include <cctype>
#include "Expression.h"
#include "Complex.h"
#include "Constant.h"
#include "Operations.h"
#include "Variable.h"
#include "Exceptions.h"


class Parser {
public:
    explicit Parser(const std::string& input) : src_(input), pos_(0) {}

    std::unique_ptr<Expression> parse() {
        skipSpaces();
        auto result = parseExpression();
        skipSpaces();
        if (pos_ < src_.size()) {
            throw ParseException(
                std::string("Unexpected character '") + src_[pos_] + "' at position " + std::to_string(pos_));
        }
        return result;
    }

private:
    std::string src_;
    size_t pos_;


    char peek() const {
        if (pos_ < src_.size()) return src_[pos_];
        return '\0';
    }

    char get() {
        return src_[pos_++];
    }

    void skipSpaces() {
        while (pos_ < src_.size() && std::isspace(static_cast<unsigned char>(src_[pos_])))
            ++pos_;
    }


    std::unique_ptr<Expression> parseExpression() {
        auto left = parseTerm();

        while (true) {
            skipSpaces();
            char c = peek();
            if (c == '+' || c == '-') {
                get();
                auto right = parseTerm();
                if (c == '+')
                    left = std::make_unique<AddOperation>(std::move(left), std::move(right));
                else
                    left = std::make_unique<SubOperations>(std::move(left), std::move(right));
            } else {
                break;
            }
        }
        return left;
    }

    std::unique_ptr<Expression> parseTerm() {
        auto left = parseFactor();

        while (true) {
            skipSpaces();
            char c = peek();
            if (c == '*' || c == '/') {
                get();
                auto right = parseFactor();
                if (c == '*')
                    left = std::make_unique<MulOperations>(std::move(left), std::move(right));
                else
                    left = std::make_unique<DivOperations>(std::move(left), std::move(right));
            } else {
                break;
            }
        }
        return left;
    }

        std::unique_ptr<Expression> parseFactor() {
        skipSpaces();
        if (peek() == '-') {
            get();
            auto operand = parseFactor();
            auto zero = std::make_unique<Constant>(0.0);
            return std::make_unique<SubOperations>(std::move(zero), std::move(operand));
        }
        return parseAtom();
    }

    std::unique_ptr<Expression> parseAtom() {
        skipSpaces();
        char c = peek();

        if (c == '(') {
            get();
            skipSpaces();

            auto complexResult = tryParseComplexLiteral();
            if (complexResult) return complexResult;

            auto expr = parseExpression();
            skipSpaces();
            if (peek() != ')') {
                throw ParseException("Expected ')' at position " + std::to_string(pos_));
            }
            get();
            return expr;
        }

        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            double num = parseNumber();
            skipSpaces();
            if (peek() == 'i') {
                get();
                return std::make_unique<Constant>(Complex(0.0, num));
            }
            return std::make_unique<Constant>(num);
        }

        if (c == 'i' && (pos_ + 1 >= src_.size() ||
            !std::isalnum(static_cast<unsigned char>(src_[pos_ + 1])))) {
            get();
            return std::make_unique<Constant>(Complex(0.0, 1.0));
        }

        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            std::string name = parseIdentifier();
            return std::make_unique<Variable>(name);
        }

        throw ParseException(std::string("Unexpected character '") + c +
                             "' at position " + std::to_string(pos_));
    }

    std::unique_ptr<Expression> tryParseComplexLiteral() {
        size_t saved = pos_;

        try {
            skipSpaces();
            double real = parseNumber();
            skipSpaces();

            char sign = peek();
            if (sign != '+' && sign != '-') {
                pos_ = saved;
                return nullptr;
            }
            get();
            skipSpaces();

            double imag = parseNumber();
            if (sign == '-') imag = -imag;

            skipSpaces();
            if (peek() != 'i') {
                pos_ = saved;
                return nullptr;
            }
            get();

            skipSpaces();
            if (peek() != ')') {
                pos_ = saved;
                return nullptr;
            }
            get();

            return std::make_unique<Constant>(Complex(real, imag));

        } catch (...) {
            pos_ = saved;
            return nullptr;
        }
    }

    double parseNumber() {
        skipSpaces();
        size_t start = pos_;
        bool hasDot = false;

        while (pos_ < src_.size()) {
            char c = src_[pos_];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                ++pos_;
            } else if (c == '.' && !hasDot) {
                hasDot = true;
                ++pos_;
            } else {
                break;
            }
        }

        if (pos_ == start) {
            throw ParseException("Expected number at position " + std::to_string(pos_));
        }

        return std::stod(src_.substr(start, pos_ - start));
    }

    std::string parseIdentifier() {
        size_t start = pos_;
        while (pos_ < src_.size() &&
               (std::isalnum(static_cast<unsigned char>(src_[pos_])) || src_[pos_] == '_'))
        {
            ++pos_;
        }
        return src_.substr(start, pos_ - start);
    }
};