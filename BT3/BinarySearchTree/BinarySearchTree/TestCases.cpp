#include "TestCases.h"
#include <iostream>
#include <iomanip>

// Test function declarations
void testSearch(NODE* root);
void testMax(NODE* root);
void testSort(NODE* root);
void testBalance(NODE* root);

// Sample tree creation
NODE* createSampleTree();
NODE* createUnbalancedTree();

// Run all tests
void runAllTests();

// Test function for search operations
void testSearch(NODE* root) {
    std::cout << "=== Testing Search Functions ===" << std::endl;
    
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
    std::cout << "=== Testing Max Functions ===" << std::endl;
    
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
    std::cout << "=== Testing Sort Function ===" << std::endl;
    
    std::cout << "Cac khoa theo thu tu tang dan: ";
    sort(root);
    std::cout << std::endl << std::endl;
}

// Test function for balance check
void testBalance(NODE* root) {
    std::cout << "=== Testing Balance Function ===" << std::endl;
    
    double alphaValues[] = {1.0, 1.5, 2.0, 3.0};
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
    
    /* The tree structure:
         50(A)
        /    \
      30(B)  70(C)
     /  \    /  \
    20(D) 40(E) 60(F) 80(G)
    */
    
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
    
    /* The tree structure:
        10(A)
          \
          20(B)
            \
            30(C)
              \
              40(D)
                \
                50(E)
    */
    
    return root;
}

// Run all tests
void runAllTests() {
    std::cout << "\n===== TESTING BALANCED BST =====" << std::endl;
    NODE* balancedTree = createSampleTree();
    
    testSearch(balancedTree);
    testMax(balancedTree);
    testSort(balancedTree);
    testBalance(balancedTree);
    
    // Free memory
    freeTree(balancedTree);
    
    std::cout << "\n===== TESTING UNBALANCED BST =====" << std::endl;
    NODE* unbalancedTree = createUnbalancedTree();
    
    testSort(unbalancedTree);
    testBalance(unbalancedTree);
    
    // Free memory
    freeTree(unbalancedTree);
}