#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>

// Token types to represent different elements in the expression
enum TokenType {
    NUMBER,       // Integer numbers
    OPERATOR,     // +, -, *, /, %, unary -, !
    VARIABLE,     // Single letter variables (a-z)
    LEFT_PAREN,   // (
    RIGHT_PAREN,  // )
    ASSIGNMENT,   // =
    SEMICOLON     // ;
};

// Token class to represent a token in the expression
class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

// Node types for the expression tree
enum NodeType {
    VALUE_NODE,
    OPERATOR_NODE,
    VARIABLE_NODE
};

// Abstract base class for expression tree nodes
class ExpressionNode {
public:
    NodeType type;

    ExpressionNode(NodeType t) : type(t) {}
    virtual ~ExpressionNode() = default;

    virtual int evaluate(std::map<char, int>& variables) = 0;
    virtual std::string toString() = 0;
};

// Node representing a numeric value
class ValueNode : public ExpressionNode {
public:
    int value;

    ValueNode(int val) : ExpressionNode(VALUE_NODE), value(val) {}

    int evaluate(std::map<char, int>& variables) override {
        return value;
    }

    std::string toString() override {
        return std::to_string(value);
    }
};

// Node representing a variable
class VariableNode : public ExpressionNode {
public:
    char name;

    VariableNode(char varName) : ExpressionNode(VARIABLE_NODE), name(varName) {}

    int evaluate(std::map<char, int>& variables) override {
        if (variables.find(name) == variables.end()) {
            throw std::runtime_error(std::string("Bien chua duoc gan gia tri: ") + name);
        }
        return variables[name];
    }

    std::string toString() override {
        return std::string(1, name);
    }
};

// Node representing an operator with operands
class OperatorNode : public ExpressionNode {
public:
    std::string op;
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;

    OperatorNode(const std::string& operation,
        ExpressionNode* leftNode = nullptr,
        ExpressionNode* rightNode = nullptr)
        : ExpressionNode(OPERATOR_NODE), op(operation),
        left(leftNode), right(rightNode) {
    }

    int evaluate(std::map<char, int>& variables) override;
    std::string toString() override;
};

// Function to tokenize an expression
std::vector<Token> tokenize(const std::string& expression);

// Function to check syntax of a tokenized expression
bool validateSyntax(const std::vector<Token>& tokens);

// Function to convert infix tokens to postfix tokens
std::vector<Token> infixToPostfix(const std::vector<Token>& tokens);

// Function to build an expression tree from tokens
std::unique_ptr<ExpressionNode> buildExpressionTree(const std::vector<Token>& postfixTokens);

// Function to evaluate an expression tree
int evaluateExpression(const std::string& expression, std::map<char, int>& variables);

// Function to get the operator precedence
int getOperatorPrecedence(const std::string& op);

// Function to check if operator is right associative
bool isRightAssociative(const std::string& op);

// Function to format expression in prefix notation
std::string toPrefix(ExpressionNode* root);

// Function to format expression in infix notation
std::string toInfix(ExpressionNode* root);

// Function to format expression in postfix notation
std::string toPostfix(ExpressionNode* root);

// Function to process a command with multiple statements
int processCommand(const std::string& command);

// Function to calculate factorial
int factorial(int n);

// Functions for test cases
void testBasicOperations();
void testComplexExpressions();
void testPrefixPostfixInfix();
void testVariableAssignments();
void testExceptionHandling();
void testFullCommands();
void runAllTests();