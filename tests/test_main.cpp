//
// Created by Максим Учунжян on 09.03.2026.
//
#include <gtest/gtest.h>
#include "Operations.h"
#include "Variable.h"
#include "Complex.h"
#include "Constant.h"
#include "Expression.h"
#include "Exceptions.h"

// tests for class Complex
TEST(ComplexTest, Constructor_Default) {
    Complex c;
    EXPECT_DOUBLE_EQ(c.real(), 0.0);
    EXPECT_DOUBLE_EQ(c.imag(), 0.0);
}

TEST(ComplexTest, Constructor_WithValues) {
    Complex c(3.0, 4.0);
    EXPECT_DOUBLE_EQ(c.real(), 3.0);
    EXPECT_DOUBLE_EQ(c.imag(), 4.0);
}

TEST(ComplexTest, Addition) {
    Complex a(1.0, 2.0);
    Complex b(3.0, 4.0);
    Complex result = a + b;

    EXPECT_DOUBLE_EQ(result.real(), 4.0);
    EXPECT_DOUBLE_EQ(result.imag(), 6.0);
}

TEST(ComplexTest, Multiplication) {
    Complex a(2.0, 3.0);
    Complex b(1.0, 4.0);
    Complex result = a * b;

    EXPECT_DOUBLE_EQ(result.real(), -10.0);
    EXPECT_DOUBLE_EQ(result.imag(), 11.0);
}

TEST(ComplexTest, Division_ByZero_ThrowsException) {
    Complex a(5.0, 3.0);
    Complex b(0.0, 0.0);

    EXPECT_THROW({
        auto result = a / b;
    }, DivisionByZeroException);
}

TEST(ComplexTest, Modulus) {
    Complex c(3.0, 4.0);
    EXPECT_DOUBLE_EQ(c.modulus(), 5.0);
}

TEST(ComplexTest, Equality) {
    Complex a(2.0, 3.0);
    Complex b(2.0, 3.0);
    Complex c(1.0, 2.0);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// tests for class Constant
TEST(ConstantTest, Constructor_FromComplex) {
    Complex val(5.0, 7.0);
    Constant c(val);

    EXPECT_DOUBLE_EQ(c.evaluate().real(), 5.0);
    EXPECT_DOUBLE_EQ(c.evaluate().imag(), 7.0);
}

TEST(ConstantTest, Constructor_FromDouble) {
    Constant c(42.0);

    EXPECT_DOUBLE_EQ(c.evaluate().real(), 42.0);
    EXPECT_DOUBLE_EQ(c.evaluate().imag(), 0.0);
}

TEST(ConstantTest, Evaluate_ReturnsValue) {
    Constant c(10.0, 20.0);
    Complex result = c.evaluate();

    EXPECT_DOUBLE_EQ(result.real(), 10.0);
    EXPECT_DOUBLE_EQ(result.imag(), 20.0);
}

TEST(ConstantTest, ToString) {
    Constant c1(3.0, 4.0);
    std::string str = c1.toString();

    EXPECT_NE(str.find("3"), std::string::npos);
    EXPECT_NE(str.find("4"), std::string::npos);
    EXPECT_NE(str.find("i"), std::string::npos);
}

TEST(ConstantTest, Clone) {
    Constant original(7.0, 8.0);
    auto clone = original.clone();

    EXPECT_DOUBLE_EQ(clone->evaluate().real(), 7.0);
    EXPECT_DOUBLE_EQ(clone->evaluate().imag(), 8.0);

    EXPECT_NE(&original, clone.get());
}

// tests for constexpr
TEST(ConstexprTest, CompileTimeComputation) {
    constexpr Complex c(1.0, 2.0);
    static_assert(c.real() == 1.0, "Real part should be 1.0");
    static_assert(c.imag() == 2.0, "Imag part should be 2.0");

    SUCCEED() << "Constexpr computation works correctly";
}


class ExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // clear and reset the context before each test
        globalContext = Context();
    }
};

// test of simple addition
TEST_F(ExpressionTest, SimpleAddition) {
    auto add = std::make_unique<AddOperation>(
        std::make_unique<Constant>(Complex(1, 2)),
        std::make_unique<Constant>(Complex(3, 4))
    );
    Complex result = add->evaluate();
    EXPECT_EQ(result.real(), 4);
    EXPECT_EQ(result.imag(), 6);
}

// testing working with variables via Context
TEST_F(ExpressionTest, VariableEvaluation) {
    globalContext.setVariable("x", Complex(10, 0));
    Variable var("x");

    EXPECT_EQ(var.evaluate().real(), 10);
    EXPECT_EQ(var.toString(), "x");
}

// complex chain of operations test: (x + y) * z
TEST_F(ExpressionTest, ComplexChain) {
    globalContext.setVariable("x", Complex(1, 0));
    globalContext.setVariable("y", Complex(2, 0));
    globalContext.setVariable("z", Complex(3, 0));

    auto add = std::make_unique<AddOperation>(
        std::make_unique<Variable>("x"),
        std::make_unique<Variable>("y")
    );
    auto mul = std::make_unique<MulOperations>(std::move(add), std::make_unique<Variable>("z"));

    EXPECT_EQ(mul->evaluate().real(), 9);
    EXPECT_EQ(mul->toString(), "((x + y) * z)");
}

// undefined variable exception test
TEST_F(ExpressionTest, UndefinedVariableThrows) {
    Variable var("unknown");
    EXPECT_THROW(var.evaluate(), UndefinedVariableException);
}

// division test
TEST_F(ExpressionTest, DivisionOperation) {
    auto div = std::make_unique<DivOperations>(
        std::make_unique<Constant>(Complex(10, 0)),
        std::make_unique<Constant>(Complex(2, 0))
    );
    EXPECT_EQ(div->evaluate().real(), 5);
}

// clone() test
TEST_F(ExpressionTest, CloneOperation) {
    auto original = std::make_unique<AddOperation>(
        std::make_unique<Constant>(Complex(1, 1)),
        std::make_unique<Constant>(Complex(2, 2))
    );

    auto cloned = original->clone();
    EXPECT_NE(original.get(), cloned.get());
    EXPECT_EQ(original->evaluate().real(), cloned->evaluate().real());
    EXPECT_EQ(original->toString(), cloned->toString());
}

// test for the presence of a variable in Context
TEST_F(ExpressionTest, ContextHasVariable) {
    globalContext.setVariable("a", Complex(0, 0));
    EXPECT_TRUE(globalContext.hasVariable("a"));
    EXPECT_FALSE(globalContext.hasVariable("b"));
}

