#include "BST.h"
#include <algorithm>
#include <cmath>

// Count the number of nodes in a tree
int countNodes(NODE* root) {
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Check if the tree is weight-balanced with coefficient alpha
int balanced(NODE* root, double alpha) {
    // Empty tree is balanced
    if (root == nullptr)
        return 1;

    // Count nodes in left and right subtrees
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);

    // Empty nodes also count as 1 for the check
    leftCount = (leftCount == 0) ? 1 : leftCount;
    rightCount = (rightCount == 0) ? 1 : rightCount;

    // Check the balance condition
    double ratio = static_cast<double>(std::max(leftCount, rightCount)) /
        static_cast<double>(std::min(leftCount, rightCount));

    if (ratio > alpha)
        return 0;

    // Recursively check for left and right subtrees
    return balanced(root->left, alpha) && balanced(root->right, alpha);
}