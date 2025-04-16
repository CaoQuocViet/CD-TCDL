#include "BST.h"
#include <iostream>

// Iterative search function
NODE* search(NODE* root, int k) {
    NODE* current = root;

    while (current != nullptr) {
        if (current->key == k)
            return current;
        else if (k < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return nullptr; // Key not found
}

// Recursive search function
NODE* searchRec(NODE* root, int k) {
    // Base case: root is null or key is present at root
    if (root == nullptr || root->key == k)
        return root;

    // Key is greater than root's key
    if (root->key < k)
        return searchRec(root->right, k);

    // Key is smaller than root's key
    return searchRec(root->left, k);
}

// Find direct children of root with key k
NODE* searchChildren(NODE* root, int k) {
    if (root == nullptr) {
        return nullptr;
    }
    
    // Check left child
    if (root->left != nullptr && root->left->key == k) {
        return root->left;
    }
    
    // Check right child
    if (root->right != nullptr && root->right->key == k) {
        return root->right;
    }
    
    // Not found
    return nullptr;
}