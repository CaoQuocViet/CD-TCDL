#pragma once

// Define BST node structure
struct NODE {
    int key;
    char data; // Sample data field (could be any type/more complex)
    NODE* left, * right;
};

// Function declarations for BST operations

// a) Search functions
NODE* search(NODE* root, int k);
NODE* searchRec(NODE* root, int k);
NODE* searchChildren(NODE* root, int k);

// b) Max value functions
NODE* max(NODE* root);
NODE* maxRec(NODE* root);

// c) Sort function
void sort(NODE* root);

// d) Balance check function
int balanced(NODE* root, double alpha);

// Utility functions
NODE* createNode(int key, char data);
void insertNode(NODE** rootRef, int key, char data);
int countNodes(NODE* root);
void displayInOrder(NODE* root); // Equivalent to sort
void freeTree(NODE* root);