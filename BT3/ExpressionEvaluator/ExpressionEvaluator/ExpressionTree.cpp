#include "ExpressionEvaluator.h"
#include <cmath>
#include <limits>

// Function to build an expression tree from postfix tokens
std::unique_ptr<ExpressionNode> buildExpressionTree(const std::vector<Token>& postfixTokens) {
    std::stack<std::unique_ptr<ExpressionNode>> nodeStack;
    
    for (const Token& token : postfixTokens) {
        if (token.type == NUMBER) {
            // Convert string to integer for number tokens
            int value = std::stoi(token.value);
            nodeStack.push(std::make_unique<ValueNode>(value));
        }
        else if (token.type == VARIABLE) {
            // Create a variable node
            char varName = token.value[0];
            nodeStack.push(std::make_unique<VariableNode>(varName));
        }
        else if (token.type == OPERATOR || token.type == ASSIGNMENT || token.type == SEMICOLON) {
            // Handle operators based on their arity
            std::unique_ptr<ExpressionNode> right;
            std::unique_ptr<ExpressionNode> left;
            
            // Pop operands from stack based on operator type
            if (token.value == "u-") {
                // Unary minus operator needs only one operand (right)
                if (nodeStack.empty()) {
                    throw std::runtime_error("Bieu thuc khong hop le: thieu toan hang cho toan tu don am");
                }
                right = std::move(nodeStack.top());
                nodeStack.pop();
                
                // Create operator node with nullptr as left operand
                auto node = std::make_unique<OperatorNode>(token.value, nullptr, right.release());
                nodeStack.push(std::move(node));
            }
            else if (token.value == "!") {
                // Factorial operator needs only one operand (right)
                if (nodeStack.empty()) {
                    throw std::runtime_error("Bieu thuc khong hop le: thieu toan hang cho giai thua");
                }
                right = std::move(nodeStack.top());
                nodeStack.pop();
                
                // Create operator node with nullptr as left operand
                auto node = std::make_unique<OperatorNode>(token.value, nullptr, right.release());
                nodeStack.push(std::move(node));
            }
            else {
                // Binary operators need two operands
                if (nodeStack.size() < 2) {
                    throw std::runtime_error("Bieu thuc khong hop le: thieu toan hang cho toan tu nhi phan");
                }
                
                right = std::move(nodeStack.top());
                nodeStack.pop();
                
                left = std::move(nodeStack.top());
                nodeStack.pop();
                
                auto node = std::make_unique<OperatorNode>(token.value, left.release(), right.release());
                nodeStack.push(std::move(node));
            }
        }
    }
    
    // At the end, nodeStack should contain exactly one node, the root of the expression tree
    if (nodeStack.size() != 1) {
        throw std::runtime_error("Bieu thuc khong hop le");
    }
    
    return std::move(nodeStack.top());
}

// Implementation of the OperatorNode::evaluate method
int OperatorNode::evaluate(std::map<char, int>& variables) {
    if (op == "u-") {
        // Unary minus operator
        if (!right) {
            throw std::runtime_error("Bieu thuc khong hop le: thieu toan hang cho toan tu don am");
        }
        return -right->evaluate(variables);
    }
    else if (op == "!") {
        // Factorial operator
        if (!right) {
            throw std::runtime_error("Bieu thuc khong hop le: thieu toan hang cho giai thua");
        }
        
        int rightValue = right->evaluate(variables);
        if (rightValue < 0) {
            throw std::runtime_error("Khong the tinh giai thua cua so am");
        }
        
        return factorial(rightValue);
    }
    else if (op == "+") {
        return left->evaluate(variables) + right->evaluate(variables);
    }
    else if (op == "-") {
        return left->evaluate(variables) - right->evaluate(variables);
    }
    else if (op == "*") {
        return left->evaluate(variables) * right->evaluate(variables);
    }
    else if (op == "/") {
        int rightValue = right->evaluate(variables);
        if (rightValue == 0) {
            throw std::runtime_error("Loi: chia cho 0");
        }
        return left->evaluate(variables) / rightValue;
    }
    else if (op == "%") {
        int rightValue = right->evaluate(variables);
        if (rightValue == 0) {
            throw std::runtime_error("Loi: chia du cho 0");
        }
        return left->evaluate(variables) % rightValue;
    }
    else if (op == "=") {
        // Assignment operator
        if (left->type != VARIABLE_NODE) {
            throw std::runtime_error("Ve trai cua phep gan phai la bien");
        }
        
        char varName = static_cast<VariableNode*>(left.get())->name;
        int rightValue = right->evaluate(variables);
        variables[varName] = rightValue;
        return rightValue;
    }
    else if (op == ";") {
        // Semicolon operator - evaluate left side, then right side, return right value
        left->evaluate(variables);
        return right->evaluate(variables);
    }
    else {
        throw std::runtime_error("Toan tu khong duoc ho tro: " + op);
    }
}

// Implementation of the OperatorNode::toString method
std::string OperatorNode::toString() {
    if (op == "u-") {
        return "-" + right->toString();
    }
    else if (op == "!") {
        return right->toString() + "!";
    }
    else {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
}

// Function to calculate factorial
int factorial(int n) {
    if (n < 0) {
        throw std::runtime_error("Khong the tinh giai thua cua so am");
    }
    
    // Use iterative approach to avoid stack overflow for large numbers
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        // Check for integer overflow
        if (result > std::numeric_limits<int>::max() / i) {
            throw std::runtime_error("Tran so khi tinh giai thua");
        }
        result *= i;
    }
    return result;
}

// Format expression in prefix notation (preorder traversal)
std::string toPrefix(ExpressionNode* root) {
    if (!root) {
        return "";
    }
    
    OperatorNode* opNode = dynamic_cast<OperatorNode*>(root);
    if (!opNode) {
        return root->toString();
    }
    
    if (opNode->op == "u-") {
        return "- " + toPrefix(opNode->right.get());
    }
    else if (opNode->op == "!") {
        return "! " + toPrefix(opNode->right.get());
    }
    else {
        return opNode->op + " " + toPrefix(opNode->left.get()) + " " + toPrefix(opNode->right.get());
    }
}

// Format expression in infix notation (inorder traversal)
std::string toInfix(ExpressionNode* root) {
    if (!root) {
        return "";
    }
    
    OperatorNode* opNode = dynamic_cast<OperatorNode*>(root);
    if (!opNode) {
        return root->toString();
    }
    
    if (opNode->op == "u-") {
        return "-" + toInfix(opNode->right.get());
    }
    else if (opNode->op == "!") {
        return toInfix(opNode->right.get()) + "!";
    }
    else if (opNode->op == ";" || opNode->op == "=") {
        return toInfix(opNode->left.get()) + " " + opNode->op + " " + toInfix(opNode->right.get());
    }
    else {
        return "(" + toInfix(opNode->left.get()) + " " + opNode->op + " " + toInfix(opNode->right.get()) + ")";
    }
}

// Format expression in postfix notation (postorder traversal)
std::string toPostfix(ExpressionNode* root) {
    if (!root) {
        return "";
    }
    
    OperatorNode* opNode = dynamic_cast<OperatorNode*>(root);
    if (!opNode) {
        return root->toString();
    }
    
    if (opNode->op == "u-") {
        return toPostfix(opNode->right.get()) + " -";
    }
    else if (opNode->op == "!") {
        return toPostfix(opNode->right.get()) + " !";
    }
    else {
        return toPostfix(opNode->left.get()) + " " + toPostfix(opNode->right.get()) + " " + opNode->op;
    }
} 