#pragma once
#include <vector>
#include <utility>

class PriorityQueue {
private:
    // Pair of <element, priority>
    std::vector<std::pair<int, int>> heap;
    // Vector to store insertion order for elements with same priority
    std::vector<int> insertionOrder;
    int currentOrder;

    void heapifyUp(int index);
    void heapifyDown(int index);
    int getParent(int index) const { return (index - 1) / 2; }
    int getLeftChild(int index) const { return 2 * index + 1; }
    int getRightChild(int index) const { return 2 * index + 2; }
    bool hasHigherPriority(int i, int j) const;

public:
    PriorityQueue() : currentOrder(0) {}

    bool isEmpty() const { return heap.empty(); }
    void insert(int element, int priority);
    int removeMax();
    int getMax() const;
    size_t size() const { return heap.size(); }
};

// Stack implementation using PriorityQueue
class Stack {
private:
    PriorityQueue pq;
    int order;
public:
    Stack() : order(0) {}
    void push(int value);
    int pop();
    bool isEmpty() const { return pq.isEmpty(); }
};

// Queue implementation using PriorityQueue
class Queue {
private:
    PriorityQueue pq;
    int order;
public:
    Queue() : order(0) {}
    void enqueue(int value);
    int dequeue();
    bool isEmpty() const { return pq.isEmpty(); }
};

// Sorting function using PriorityQueue
void heapSort(std::vector<int>& arr);