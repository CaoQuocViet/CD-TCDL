#include "ExpressionEvaluator.h"
#include <cctype>
#include <algorithm>

// Check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '!';
}

// Check if a token is potentially a unary operator (specifically for minus)
bool isUnaryMinus(const std::vector<Token>& tokens, size_t currentIndex) {
    if (currentIndex == 0) {
        return true; // First token can be unary minus
    }
    
    // Check previous token type
    const Token& prevToken = tokens[currentIndex - 1];
    return prevToken.type == OPERATOR || prevToken.type == LEFT_PAREN || 
           prevToken.type == ASSIGNMENT || prevToken.type == SEMICOLON;
}

// Function to tokenize an expression
std::vector<Token> tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    std::string temp;
    
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        
        // Skip whitespace
        if (std::isspace(c)) {
            continue;
        }
        
        // Handle numbers
        if (std::isdigit(c)) {
            temp = "";
            while (i < expression.length() && std::isdigit(expression[i])) {
                temp += expression[i++];
            }
            i--; // Move back one position
            tokens.push_back(Token(NUMBER, temp));
        }
        // Handle variables (single letters)
        else if (std::isalpha(c)) {
            // Only single lowercase letters are valid variables in our implementation
            if (std::islower(c)) {
                tokens.push_back(Token(VARIABLE, std::string(1, c)));
            } else {
                throw std::runtime_error("Ten bien khong hop le: " + std::string(1, c));
            }
        }
        // Handle left parenthesis
        else if (c == '(') {
            tokens.push_back(Token(LEFT_PAREN, "("));
        }
        // Handle right parenthesis
        else if (c == ')') {
            tokens.push_back(Token(RIGHT_PAREN, ")"));
        }
        // Handle assignment
        else if (c == '=') {
            tokens.push_back(Token(ASSIGNMENT, "="));
        }
        // Handle semicolon
        else if (c == ';') {
            tokens.push_back(Token(SEMICOLON, ";"));
        }
        // Handle operators
        else if (isOperator(c)) {
            // Special handling for negative sign (unary minus)
            if (c == '-' && (tokens.empty() || isUnaryMinus(tokens, tokens.size()))) {
                tokens.push_back(Token(OPERATOR, "u-")); // Mark as unary minus
            } else {
                tokens.push_back(Token(OPERATOR, std::string(1, c)));
            }
        }
        else {
            throw std::runtime_error("Ky tu khong hop le: " + std::string(1, c));
        }
    }
    
    return tokens;
}

// Get operator precedence
int getOperatorPrecedence(const std::string& op) {
    if (op == "u-") return 5;     // Unary minus has higher precedence
    if (op == "!") return 6;      // Factorial has highest precedence
    if (op == "*" || op == "/" || op == "%") return 4;
    if (op == "+" || op == "-") return 3;
    if (op == "=") return 2;
    if (op == ";") return 1;
    return 0;
}

// Check if operator is right associative
bool isRightAssociative(const std::string& op) {
    return op == "u-" || op == "!"; // Unary operators are right associative
}

// Validate syntax of tokenized expression
bool validateSyntax(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        return false; // Empty expression is invalid
    }
    
    int parenCount = 0;
    bool expectOperand = true;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        
        // Check parentheses count
        if (token.type == LEFT_PAREN) {
            parenCount++;
            expectOperand = true;
        }
        else if (token.type == RIGHT_PAREN) {
            parenCount--;
            if (parenCount < 0) {
                return false; // Unmatched closing parenthesis
            }
            expectOperand = false;
        }
        // Check for proper operand/operator sequence
        else if (token.type == NUMBER || token.type == VARIABLE) {
            if (!expectOperand && i > 0 && 
                (tokens[i-1].type == NUMBER || tokens[i-1].type == VARIABLE || tokens[i-1].type == RIGHT_PAREN)) {
                return false; // Two operands without operator
            }
            expectOperand = false;
        }
        else if (token.type == OPERATOR) {
            // Special handling for unary minus and factorial
            if (token.value == "u-") {
                expectOperand = true;
            }
            else if (token.value == "!") {
                if (expectOperand) {
                    return false; // Factorial needs an operand before it
                }
                // expectOperand stays false after factorial
            }
            else {
                // Binary operators
                if (expectOperand) {
                    return false; // Binary operator without left operand
                }
                expectOperand = true;
            }
        }
        else if (token.type == ASSIGNMENT) {
            // Assignment needs a variable before it
            if (i == 0 || tokens[i-1].type != VARIABLE) {
                return false;
            }
            expectOperand = true;
        }
        else if (token.type == SEMICOLON) {
            // Semicolon should not be followed by another semicolon
            if (i > 0 && tokens[i-1].type == SEMICOLON) {
                return false;
            }
            expectOperand = true;
        }
    }
    
    // Check if parentheses are balanced
    if (parenCount != 0) {
        return false;
    }
    
    // Check if expression doesn't end with a binary operator
    if (expectOperand) {
        return false; // Expression ends with an operator
    }
    
    return true;
}

// Convert infix tokens to postfix tokens using Shunting Yard algorithm
std::vector<Token> infixToPostfix(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::stack<Token> operatorStack;
    
    for (const Token& token : tokens) {
        switch (token.type) {
            case NUMBER:
            case VARIABLE:
                output.push_back(token);
                break;
                
            case OPERATOR:
                while (!operatorStack.empty() && operatorStack.top().type == OPERATOR &&
                       ((isRightAssociative(token.value) && 
                         getOperatorPrecedence(token.value) < getOperatorPrecedence(operatorStack.top().value)) ||
                        (!isRightAssociative(token.value) && 
                         getOperatorPrecedence(token.value) <= getOperatorPrecedence(operatorStack.top().value)))) {
                    output.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
                
            case LEFT_PAREN:
                operatorStack.push(token);
                break;
                
            case RIGHT_PAREN:
                while (!operatorStack.empty() && operatorStack.top().type != LEFT_PAREN) {
                    output.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                
                if (!operatorStack.empty() && operatorStack.top().type == LEFT_PAREN) {
                    operatorStack.pop(); // Discard the left parenthesis
                } else {
                    throw std::runtime_error("Dau ngoac khong khop");
                }
                break;
                
            case ASSIGNMENT:
            case SEMICOLON:
                // Handle like operators
                while (!operatorStack.empty() && operatorStack.top().type != LEFT_PAREN) {
                    output.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
        }
    }
    
    // Pop any remaining operators from the stack to the output
    while (!operatorStack.empty()) {
        if (operatorStack.top().type == LEFT_PAREN) {
            throw std::runtime_error("Dau ngoac khong khop");
        }
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }
    
    return output;
} 