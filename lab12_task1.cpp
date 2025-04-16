#include <iostream>
#include <memory>
#include <string>

class Expression;

class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() const = 0;
    virtual std::string toString() const = 0;
};

// Terminal Expression
class NumberExpression : public Expression {
    int value;
public:
    explicit NumberExpression(int value) : value(value) {}

    int interpret() const override {
        return value;
    }

    std::string toString() const override {
        return std::to_string(value);
    }
};

class AddExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret() const override {
        return left->interpret() + right->interpret();
    }

    std::string toString() const override {
        return "(" + left->toString() + " + " + right->toString() + ")";
    }
};

class SubtractExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    SubtractExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret() const override {
        return left->interpret() - right->interpret();
    }

    std::string toString() const override {
        return "(" + left->toString() + " - " + right->toString() + ")";
    }
};

class MultiplyExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    MultiplyExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret() const override {
        return left->interpret() * right->interpret();
    }

    std::string toString() const override {
        return "(" + left->toString() + " * " + right->toString() + ")";
    }
};

// Demonstration
int main() {
    // Build the expression: (5 + 3) * (10 - 2)
    auto expr = std::make_unique<MultiplyExpression>(
        std::make_unique<AddExpression>(
            std::make_unique<NumberExpression>(5),
            std::make_unique<NumberExpression>(3)
        ),
        std::make_unique<SubtractExpression>(
            std::make_unique<NumberExpression>(10),
            std::make_unique<NumberExpression>(2)
        )
    );

    std::cout << "Expression: " << expr->toString() << std::endl;

    int result = expr->interpret();
    std::cout << "Result: " << result << std::endl;

    return 0;
}