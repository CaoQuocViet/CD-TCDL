#include "TestCases.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <stdexcept>

// Test basic arithmetic operations
void testBasicOperations() {
    std::cout << "\n=== TEST CAC PHEP TOAN CO BAN ===\n";
    
    // Addition and subtraction
    std::cout << "\nPhep cong va tru:\n";
    displayExpressionForms("3 + 5");
    displayExpressionForms("10 - 4");
    displayExpressionForms("3 + 5 - 2");
    
    // Multiplication and division
    std::cout << "\nPhep nhan va chia:\n";
    displayExpressionForms("4 * 7");
    displayExpressionForms("20 / 4");
    displayExpressionForms("5 * 3 / 2");
    
    // Modulo
    std::cout << "\nPhep chia lay du:\n";
    displayExpressionForms("17 % 5");
    
    // Unary minus
    std::cout << "\nPhep doi dau:\n";
    displayExpressionForms("-7");
    displayExpressionForms("-(3 + 4)");
    
    // Factorial
    std::cout << "\nPhep giai thua:\n";
    displayExpressionForms("5!");
    displayExpressionForms("(3 + 2)!");
}

// Test complex expressions with multiple operations
void testComplexExpressions() {
    std::cout << "\n=== TEST BIEU THUC PHUC TAP ===\n";
    
    // Multiple operations and precedence
    std::cout << "\nNhieu phep toan va do uu tien:\n";
    displayExpressionForms("3 + 4 * 2");
    displayExpressionForms("(3 + 4) * 2");
    displayExpressionForms("10 - 3 * 2 + 5");
    
    // Nested parentheses
    std::cout << "\nDau ngoac long nhau:\n";
    displayExpressionForms("((2 + 3) * (4 - 1))");
    
    // Combined operators
    std::cout << "\nKet hop nhieu phep toan:\n";
    displayExpressionForms("1 - (2 - 3) * (4 + 5)!");
    displayExpressionForms("20 / 4 + 3 * 2!");
    displayExpressionForms("-3 * 4 + 7 * 2");
}

// Test notation conversions
void testPrefixPostfixInfix() {
    std::cout << "\n=== TEST CHUYEN DOI KI PHAP ===\n";
    
    std::cout << "\nChuyen doi ki phap (tien to, trung to, hau to):\n";
    displayExpressionForms("3 + 4 * 2");
    displayExpressionForms("(a + b) * 5");
    displayExpressionForms("1 - (2 - 3) * (4 + 5)!");
}

// Test variable assignments
void testVariableAssignments() {
    std::cout << "\n=== TEST GAN BIEN ===\n";
    
    try {
        std::cout << "\nGan bien don gian:\n";
        std::cout << "a = 5\n";
        int result = processCommand("a = 5");
        std::cout << "Ket qua: " << result << std::endl;
        
        std::cout << "\nSu dung bien da gan:\n";
        std::cout << "a = 5; a + 3\n";
        result = processCommand("a = 5; a + 3");
        std::cout << "Ket qua: " << result << std::endl;
        
        std::cout << "\nNhieu bien va phep toan:\n";
        std::cout << "a = 1; b = 10 * a; a + 20 * b\n";
        result = processCommand("a = 1; b = 10 * a; a + 20 * b");
        std::cout << "Ket qua: " << result << std::endl;
        
        std::cout << "\nPhep gan long nhau:\n";
        std::cout << "a = b = 5; a * b\n";
        result = processCommand("a = b = 5; a * b");
        std::cout << "Ket qua: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Loi: " << e.what() << std::endl;
    }
}

// Test exception handling
void testExceptionHandling() {
    std::cout << "\n=== TEST XU LY NGOAI LE ===\n";
    
    // Test case 1: Division by zero
    std::cout << "\nChia cho 0:\n";
    std::cout << "5 / 0\n";
    try {
        displayExpressionForms("5 / 0");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 2: Unmatched parentheses
    std::cout << "\nDau ngoac khong khop:\n";
    std::cout << "(3 + 4 * (2 - 1\n";
    try {
        displayExpressionForms("(3 + 4 * (2 - 1");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 3: Invalid operators
    std::cout << "\nToan tu khong hop le:\n";
    std::cout << "3 @ 5\n";
    try {
        displayExpressionForms("3 @ 5");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 4: Factorial of negative number
    std::cout << "\nGiai thua cua so am:\n";
    std::cout << "(-3)!\n";
    try {
        displayExpressionForms("(-3)!");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 5: Missing operand
    std::cout << "\nThieu toan hang:\n";
    std::cout << "3 + * 5\n";
    try {
        displayExpressionForms("3 + * 5");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 6: Missing operator
    std::cout << "\nThieu toan tu:\n";
    std::cout << "3 5\n";
    try {
        displayExpressionForms("3 5");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
    
    // Test case 7: Undefined variable
    std::cout << "\nBien chua duoc dinh nghia:\n";
    std::cout << "a + 5\n";
    try {
        displayExpressionForms("a + 5");
    }
    catch (const std::exception& e) {
        std::cout << "Loi (captured): " << e.what() << std::endl;
    }
}

// Test full commands with multiple statements
void testFullCommands() {
    std::cout << "\n=== TEST LENH PHUC TAP ===\n";
    
    try {
        std::cout << "\nVi du 1: a = 1; b = 10 * a; a + 20 * b\n";
        int result = processCommand("a = 1; b = 10 * a; a + 20 * b");
        std::cout << "Ket qua: " << result << std::endl;
        
        std::cout << "\nVi du 2: a = 5; b = a * 2; c = b - a; c * 3\n";
        result = processCommand("a = 5; b = a * 2; c = b - a; c * 3");
        std::cout << "Ket qua: " << result << std::endl;
        
        std::cout << "\nVi du 3: a = 3!; b = 2 * a; a + b\n";
        result = processCommand("a = 3!; b = 2 * a; a + b");
        std::cout << "Ket qua: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Loi: " << e.what() << std::endl;
    }
}

// Run all tests
void runAllTests() {
    std::cout << "=====================================\n";
    std::cout << "      BAT DAU CHAY CAC TEST CASE    \n";
    std::cout << "=====================================\n";
    
    // Run all test functions
    testBasicOperations();
    testComplexExpressions();
    testPrefixPostfixInfix();
    testVariableAssignments();
    testExceptionHandling();
    testFullCommands();
    
    std::cout << "\n=====================================\n";
    std::cout << "      KET THUC CAC TEST CASE        \n";
    std::cout << "=====================================\n";
} 