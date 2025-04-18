#pragma once
#include "BST.h"

// Test function declarations
void testSearch(NODE* root);
void testSearchChildren(NODE* root);
void testMax(NODE* root);
void testSort(NODE* root);
void testBalance(NODE* root);

// Sample tree creation
NODE* createSampleTree();
NODE* createUnbalancedTree();
NODE* createComplexTree(); 

// Run all tests
void runAllTests();