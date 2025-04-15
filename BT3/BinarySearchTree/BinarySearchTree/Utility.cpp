#include "BST.h"
#include <iostream>

// Create a new node
NODE* createNode(int key, char data) {
    NODE* newNode = new NODE();
    newNode->key = key;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Insert a new node with given key
void insertNode(NODE** root, int key, char data) {
    // If the tree is empty, create a new node and make it root
    if (*root == nullptr) {
        *root = createNode(key, data);
        return;
    }

    // Otherwise, recur down the tree
    if (key < (*root)->key)
        insertNode(&((*root)->left), key, data);
    else if (key > (*root)->key)
        insertNode(&((*root)->right), key, data);
    // Equal keys are not allowed in BST
    else
        std::cout << "Duplicate key not allowed: " << key << std::endl;
}

// Free the memory allocated for the tree
void freeTree(NODE* root) {
    if (root == nullptr)
        return;

    // Post-order traversal to delete the tree
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}