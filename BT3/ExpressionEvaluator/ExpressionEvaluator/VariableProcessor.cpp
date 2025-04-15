#include "ExpressionEvaluator.h"
#include <sstream>
#include <vector>
#include <iostream>

// Function to evaluate an expression
int evaluateExpression(const std::string& expression, std::map<char, int>& variables) {
    try {
        // Tokenize the expression
        std::vector<Token> tokens = tokenize(expression);

        // Validate syntax
        if (!validateSyntax(tokens)) {
            throw std::runtime_error("Bieu thuc khong hop le");
        }

        // Convert to postfix
        std::vector<Token> postfixTokens = infixToPostfix(tokens);

        // Build expression tree
        std::unique_ptr<ExpressionNode> expressionTree = buildExpressionTree(postfixTokens);

        // Evaluate the tree
        return expressionTree->evaluate(variables);
    }
    catch (const std::exception& e) {
        throw; // Re-throw the exception
    }
}

// Function to process a command with multiple statements
int processCommand(const std::string& command) {
    std::map<char, int> variables;

    // Split command by semicolons
    std::vector<std::string> statements;
    std::string temp;
    std::istringstream iss(command);

    // First split into statements
    while (std::getline(iss, temp, ';')) {
        statements.push_back(temp);
    }

    if (statements.empty()) {
        throw std::runtime_error("Lenh trong");
    }

    // Process each statement
    std::string combinedExpression;
    for (size_t i = 0; i < statements.size(); ++i) {
        if (i > 0) {
            combinedExpression += " ; ";
        }
        combinedExpression += statements[i];
    }

    // Evaluate the combined expression
    return evaluateExpression(combinedExpression, variables);
}

// Helper function to display expression in all forms
void displayExpressionForms(const std::string& expression) {
    try {
        std::map<char, int> variables;

        // Tokenize and build expression tree
        std::vector<Token> tokens = tokenize(expression);
        std::vector<Token> postfixTokens = infixToPostfix(tokens);
        std::unique_ptr<ExpressionNode> expressionTree = buildExpressionTree(postfixTokens);

        // Display all forms
        std::cout << "Bieu thuc dang tien to: " << toPrefix(expressionTree.get()) << std::endl;
        std::cout << "Bieu thuc dang trung to: " << toInfix(expressionTree.get()) << std::endl;
        std::cout << "Bieu thuc dang hau to: " << toPostfix(expressionTree.get()) << std::endl;

        // Evaluate and display result
        int result = expressionTree->evaluate(variables);
        std::cout << "Ket qua: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Loi: " << e.what() << std::endl;
    }
}