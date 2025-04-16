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
        if (!temp.empty()) {
            // Trim leading and trailing whitespaces
            size_t first = temp.find_first_not_of(" \t\n\r");
            size_t last = temp.find_last_not_of(" \t\n\r");
            if (first != std::string::npos && last != std::string::npos) {
                statements.push_back(temp.substr(first, last - first + 1));
            }
            else if (first != std::string::npos) {
                statements.push_back(temp.substr(first));
            }
            else if (last != std::string::npos) {
                statements.push_back(temp.substr(0, last + 1));
            }
        }
    }

    if (statements.empty()) {
        throw std::runtime_error("Lenh trong");
    }

    int result = 0;
    // Process each statement
    for (size_t i = 0; i < statements.size(); ++i) {
        std::string stmt = statements[i];
        
        // Check if statement is an assignment
        size_t equalsPos = stmt.find('=');
        if (equalsPos != std::string::npos && equalsPos > 0 && equalsPos < stmt.length() - 1) {
            // Get variable name (left side)
            std::string varStr = stmt.substr(0, equalsPos);
            varStr.erase(0, varStr.find_first_not_of(" \t\r\n"));
            varStr.erase(varStr.find_last_not_of(" \t\r\n") + 1);
            
            if (varStr.length() != 1 || !isalpha(varStr[0])) {
                throw std::runtime_error("Ve trai cua phep gan phai la bien (chu cai)");
            }
            
            char varName = varStr[0];
            
            // Get expression (right side)
            std::string exprStr = stmt.substr(equalsPos + 1);
            exprStr.erase(0, exprStr.find_first_not_of(" \t\r\n"));
            exprStr.erase(exprStr.find_last_not_of(" \t\r\n") + 1);
            
            // Evaluate expression
            result = evaluateExpression(exprStr, variables);
            
            // Store result in variable
            variables[varName] = result;
        }
        else {
            // Just an expression to evaluate
            result = evaluateExpression(stmt, variables);
        }
    }

    return result;
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