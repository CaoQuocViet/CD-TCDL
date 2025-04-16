#include "TestCases.h"
#include <iostream>
#include <iomanip>

// Test function for search operations
void testSearch(NODE* root) {
    std::cout << "=== Kiem tra chuc nang tim kiem ===" << std::endl;
    
    int searchKeys[] = {50, 30, 70, 20, 40, 60, 80, 100};
    for (int key : searchKeys) {
        // Test iterative search
        NODE* found = search(root, key);
        std::cout << "Tim khoa " << key << " bang phuong phap lap: ";
        if (found)
            std::cout << "Tim thay, data = " << found->data << std::endl;
        else
            std::cout << "Khong tim thay" << std::endl;
        
        // Test recursive search
        found = searchRec(root, key);
        std::cout << "Tim khoa " << key << " bang de quy: ";
        if (found)
            std::cout << "Tim thay, data = " << found->data << std::endl;
        else
            std::cout << "Khong tim thay" << std::endl;
    }
    std::cout << std::endl;
}

// Test function for max operations
void testMax(NODE* root) {
    std::cout << "=== Kiem tra chuc nang tim gia tri lon nhat ===" << std::endl;
    
    NODE* maxNode = max(root);
    std::cout << "Khoa lon nhat (lap): ";
    if (maxNode)
        std::cout << maxNode->key << ", data = " << maxNode->data << std::endl;
    else
        std::cout << "Cay rong" << std::endl;
    
    maxNode = maxRec(root);
    std::cout << "Khoa lon nhat (de quy): ";
    if (maxNode)
        std::cout << maxNode->key << ", data = " << maxNode->data << std::endl;
    else
        std::cout << "Cay rong" << std::endl;
    
    std::cout << std::endl;
}

// Test function for sorting
void testSort(NODE* root) {
    std::cout << "=== Kiem tra chuc nang sap xep ===" << std::endl;
    
    std::cout << "Cac khoa theo thu tu tang dan: ";
    sort(root);
    std::cout << std::endl << std::endl;
}

// Test function for balance check
void testBalance(NODE* root) {
    std::cout << "=== Kiem tra chuc nang can bang ===" << std::endl;
    
    double alphaValues[] = {1.0, 1.5, 2.0, 3.0, 4.1, 5.2};
    for (double alpha : alphaValues) {
        int isBalanced = balanced(root, alpha);
        std::cout << "Cay " << (isBalanced ? "can bang" : "khong can bang");
        std::cout << " voi he so alpha = " << std::fixed << std::setprecision(1) << alpha << std::endl;
    }
    
    std::cout << std::endl;
}

// Function to create a sample tree
NODE* createSampleTree() {
    NODE* root = nullptr;
    
    // Insert some nodes with keys and data
    insertNode(&root, 50, 'A');
    insertNode(&root, 30, 'B');
    insertNode(&root, 70, 'C');
    insertNode(&root, 20, 'D');
    insertNode(&root, 40, 'E');
    insertNode(&root, 60, 'F');
    insertNode(&root, 80, 'G');
    
    std::cout << "    /* Cau truc cay:\n";
    std::cout << "               50(A)\n";
    std::cout << "             /       \\\n";
    std::cout << "         30(B)       70(C)\n";
    std::cout << "        /     \\     /     \\\n";
    std::cout << "     20(D)  40(E) 60(F)  80(G)\n";
    std::cout << "    */\n";
    
    return root;
}

// Function to create an unbalanced tree
NODE* createUnbalancedTree() {
    NODE* root = nullptr;
    
    // Create a right-skewed tree
    insertNode(&root, 10, 'A');
    insertNode(&root, 20, 'B');
    insertNode(&root, 30, 'C');
    insertNode(&root, 40, 'D');
    insertNode(&root, 50, 'E');
    
    std::cout << "    /* Cau truc cay:\n";
    std::cout << "        10(A)\n";
    std::cout << "          \\\n";
    std::cout << "          20(B)\n";
    std::cout << "            \\\n";
    std::cout << "            30(C)\n";
    std::cout << "              \\\n";
    std::cout << "              40(D)\n";
    std::cout << "                \\\n";
    std::cout << "                50(E)\n";
    std::cout << "    */\n";

    return root;
}

// Function to create a complex tree
NODE* createComplexTree() {
    NODE* root = nullptr;
    
    // Create a more complex tree with 15 nodes
    insertNode(&root, 50, 'A');
    insertNode(&root, 25, 'B');
    insertNode(&root, 75, 'C');
    insertNode(&root, 15, 'D');
    insertNode(&root, 35, 'E');
    insertNode(&root, 65, 'F');
    insertNode(&root, 85, 'G');
    insertNode(&root, 10, 'H');
    insertNode(&root, 20, 'I');
    insertNode(&root, 30, 'J');
    insertNode(&root, 40, 'K');
    insertNode(&root, 60, 'L');
    insertNode(&root, 70, 'M');
    insertNode(&root, 80, 'N');
    insertNode(&root, 90, 'O');
    
    std::cout << "    /* Cau truc cay phuc tap:\n";
    std::cout << "                                50(A)\n";
    std::cout << "                       /                     \\\n";
    std::cout << "                 25(B)                         75(C)\n";
    std::cout << "              /        \\                   /         \\\n";
    std::cout << "         15(D)          35(E)         65(F)          85(G)\n";
    std::cout << "        /     \\        /     \\       /     \\        /     \\\n";
    std::cout << "   10(H)     20(I)  30(J)  40(K)  60(L)  70(M)   80(N)   90(O)\n";
    std::cout << "    */\n\n";
    
    return root;
}

// Run all tests
void runAllTests() {
    std::cout << "\n===== KIEM TRA CAY CAN BANG =====" << std::endl;
    NODE* balancedTree = createSampleTree();
    
    testSearch(balancedTree);
    testMax(balancedTree);
    testSort(balancedTree);
    testBalance(balancedTree);
    
    // Free memory
    freeTree(balancedTree);
    
    std::cout << "\n===== KIEM TRA CAY KHONG CAN BANG =====" << std::endl;
    NODE* unbalancedTree = createUnbalancedTree();
    
    testSort(unbalancedTree);
    testBalance(unbalancedTree);
    
    // Free memory
    freeTree(unbalancedTree);
    
    std::cout << "\n===== KIEM TRA CAY PHUC TAP =====" << std::endl;
    NODE* complexTree = createComplexTree();
    
    testSearch(complexTree);
    testMax(complexTree);
    testSort(complexTree);
    testBalance(complexTree);
    
    // Free memory
    freeTree(complexTree);
}