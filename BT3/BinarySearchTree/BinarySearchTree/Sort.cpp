#include "BST.h"
#include <iostream>

// Function to print all keys in ascending order (in-order traversal)
void sort(NODE* root) {
    // Base case
    if (root == nullptr)
        return;
    
    // First recur on left subtree
    sort(root->left);
    
    // Print the key (in-order)
    std::cout << root->key << " ";
    
    // Then recur on right subtree
    sort(root->right);
}

// Alternative implementation with the same functionality
void displayInOrder(NODE* root) {
    if (root == nullptr)
        return;
    
    displayInOrder(root->left);
    std::cout << root->key << " ";
    displayInOrder(root->right);
} 