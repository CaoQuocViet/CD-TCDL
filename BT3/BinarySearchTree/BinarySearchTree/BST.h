#pragma once

struct NODE {
    int key;
    char data; // Sample data field (could be any type/more complex)
    NODE* left, * right;
};

// Function to search for a node with key k using iteration
NODE* search(NODE* root, int k);

// Function to search for a node with key k using recursion
NODE* searchRec(NODE* root, int k);

// Function to find the node with maximum key using iteration
NODE* max(NODE* root);

// Function to find the node with maximum key using recursion
NODE* maxRec(NODE* root);

// Function to print all keys in ascending order
void sort(NODE* root);

// Function to check if the tree is weight-balanced with coefficient alpha
int balanced(NODE* root, double alpha);

// Helper functions
NODE* createNode(int key, char data);
void insertNode(NODE** root, int key, char data);
int countNodes(NODE* root);
void displayInOrder(NODE* root); // Equivalent to sort
void freeTree(NODE* root);