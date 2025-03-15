#include "PriorityQueue.h"
#include <stdexcept>

bool PriorityQueue::hasHigherPriority(int i, int j) const {
    // If priorities are equal, use insertion order (smaller order = higher priority)
    if (heap[i].second == heap[j].second) {
        return insertionOrder[i] < insertionOrder[j];
    }
    // Smaller priority value means higher priority
    return heap[i].second < heap[j].second;
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = getParent(index);
        if (hasHigherPriority(index, parent)) {
            std::swap(heap[index], heap[parent]);
            std::swap(insertionOrder[index], insertionOrder[parent]);
            index = parent;
        }
        else {
            break;
        }
    }
}

void PriorityQueue::heapifyDown(int index) {
    int size = heap.size();
    while (true) {
        int smallest = index;
        int left = getLeftChild(index);
        int right = getRightChild(index);

        if (left < size && hasHigherPriority(left, smallest)) {
            smallest = left;
        }
        if (right < size && hasHigherPriority(right, smallest)) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            std::swap(insertionOrder[index], insertionOrder[smallest]);
            index = smallest;
        }
        else {
            break;
        }
    }
}

void PriorityQueue::insert(int element, int priority) {
    heap.push_back({ element, priority });
    insertionOrder.push_back(currentOrder++);
    heapifyUp(heap.size() - 1);
}

int PriorityQueue::removeMax() {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }

    int maxElement = heap[0].first;
    heap[0] = heap.back();
    insertionOrder[0] = insertionOrder.back();
    heap.pop_back();
    insertionOrder.pop_back();

    if (!isEmpty()) {
        heapifyDown(0);
    }

    return maxElement;
}

int PriorityQueue::getMax() const {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap[0].first;
}

// Stack implementation
void Stack::push(int value) {
    // For stack, newer elements have higher priority (smaller number)
    pq.insert(value, -order++);
}

int Stack::pop() {
    if (pq.isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return pq.removeMax();
}

// Queue implementation
void Queue::enqueue(int value) {
    // For queue, older elements have higher priority (smaller number)
    pq.insert(value, order++);
}

int Queue::dequeue() {
    if (pq.isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return pq.removeMax();
}

// Sorting implementation using priority queue
void heapSort(std::vector<int>& arr) {
    PriorityQueue pq;
    // Insert all elements
    for (int num : arr) {
        pq.insert(num, num);
    }

    // Extract elements in order
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = pq.removeMax();
    }
}