#include "BST.h"

// Iterative function to find the maximum key
NODE* max(NODE* root) {
    // Empty tree
    if (root == nullptr)
        return nullptr;

    // Traverse to the rightmost node
    NODE* current = root;
    while (current->right != nullptr)
        current = current->right;

    return current;
}

// Recursive function to find the maximum key
NODE* maxRec(NODE* root) {
    // Base cases: empty tree or rightmost node
    if (root == nullptr)
        return nullptr;

    if (root->right == nullptr)
        return root;

    // Recursively find maximum in right subtree
    return maxRec(root->right);
}