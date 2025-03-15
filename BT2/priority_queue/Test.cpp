#include <iostream>
#include "Test.h"
#include "PriorityQueue.h"
#include <vector>

// a) Test Priority Queue implementation
void testPriorityQueueBasic() {
    std::cout << "\n=== Test Basic Priority Queue Operations ===\n";
    
    PriorityQueue pq;
    std::cout << "1. Test empty queue:\n";
    std::cout << "   Queue is empty: " << (pq.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "   Inserting: (value: 10, priority: 1)\n";
	pq.insert(10, 1);
	std::cout << "   Queue is empty: " << (pq.isEmpty() ? "true" : "false") << std::endl;
	pq.removeMax();

    std::cout << "\n2. Test insertion with different priorities:\n";
    std::cout << "   Inserting: (value: 5, priority: 2)\n";
    std::cout << "   Inserting: (value: 3, priority: 1)\n";
    std::cout << "   Inserting: (value: 7, priority: 3)\n";
    std::cout << "   Inserting: (value: 1, priority: 0)\n";
    
    pq.insert(5, 2);
    pq.insert(3, 1);
    pq.insert(7, 3);
    pq.insert(1, 0);

    std::cout << "\n3. Test removal (should be in priority order - smallest priority first):\n";
    std::cout << "   Expected order: 1, 3, 5, 7\n";
    std::cout << "   Actual order:\n";
    while (!pq.isEmpty()) {
        std::cout << "   Removed: " << pq.removeMax() << std::endl;
    }

    std::cout << "\n4. Test empty after removal:\n";
    std::cout << "   Queue is empty: " << (pq.isEmpty() ? "true" : "false") << std::endl;

    std::cout << "\n5. Test exception on empty queue:\n";
    try {
        pq.removeMax();
        std::cout << "   Error: Should have thrown exception\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "   Successfully caught exception: " << e.what() << std::endl;
    }
}

void testPriorityQueueSamePriority() {
    std::cout << "\n=== Test Priority Queue with Same Priority (FIFO Order) ===\n";
    
    PriorityQueue pq;
    
    std::cout << "1. Test insertion with same priority:\n";
    std::cout << "   Inserting three elements with priority 1:\n";
    std::cout << "   First:  (value: 10, priority: 1)\n";
    std::cout << "   Second: (value: 20, priority: 1)\n";
    std::cout << "   Third:  (value: 30, priority: 1)\n";
    
    pq.insert(10, 1);
    pq.insert(20, 1);
    pq.insert(30, 1);

    std::cout << "\n2. Test removal (should maintain FIFO order):\n";
    std::cout << "   Expected order: 10, 20, 30\n";
    std::cout << "   Actual order:\n";
    while (!pq.isEmpty()) {
        std::cout << "   Removed: " << pq.removeMax() << std::endl;
    }

    std::cout << "\n3. Test mixed priorities with duplicates:\n";
    std::cout << "   Inserting: (value: 1, priority: 0)\n";
    std::cout << "   Inserting: (value: 2, priority: 0)\n";
    std::cout << "   Inserting: (value: 3, priority: 1)\n";
    std::cout << "   Inserting: (value: 4, priority: 1)\n";
    
    pq.insert(1, 0);
    pq.insert(2, 0);
    pq.insert(3, 1);
    pq.insert(4, 1);

    std::cout << "\n   Removing elements (should maintain both priority and FIFO):\n";
    std::cout << "   Expected order: 1, 2, 3, 4\n";
    std::cout << "   Actual order:\n";
    while (!pq.isEmpty()) {
        std::cout << "   Removed: " << pq.removeMax() << std::endl;
    }
}

// b) Test sorting using Priority Queue
void testHeapSort() {
    std::cout << "\n=== Test Heap Sort Implementation ===\n";
    
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "1. Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    heapSort(arr);

    std::cout << "2. Sorted array:   ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Test with duplicates
    std::vector<int> arr2 = {5, 2, 8, 5, 1, 9, 2, 8};
    std::cout << "\n3. Array with duplicates:\n";
    std::cout << "   Original: ";
    for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    heapSort(arr2);

    std::cout << "   Sorted:   ";
    for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// c) Test Stack implementation using Priority Queue
void testStackImplementation() {
    std::cout << "\n=== Test Stack Implementation (LIFO using Priority Queue) ===\n";
    
    Stack stack;
    std::cout << "1. Test empty stack:\n";
    std::cout << "   Stack is empty: " << (stack.isEmpty() ? "true" : "false") << std::endl;
    std::cout << "   Pushing: 10\n";
    stack.push(10);
    std::cout << "   Stack is empty: " << (stack.isEmpty() ? "true" : "false") << std::endl;
	stack.pop();

    std::cout << "\n2. Test push operation:\n";
    std::cout << "   Pushing: 1, 2, 3, 4\n";
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    std::cout << "\n3. Test pop operation (should be LIFO order):\n";
    std::cout << "   Expected order: 4, 3, 2, 1\n";
    std::cout << "   Actual order:\n";
    while (!stack.isEmpty()) {
        std::cout << "   Popped: " << stack.pop() << std::endl;
    }

    std::cout << "\n4. Test empty stack operations:\n";
    std::cout << "   Stack is empty: " << (stack.isEmpty() ? "true" : "false") << std::endl;
    
    std::cout << "\n5. Test exception on empty stack:\n";
    try {
        stack.pop();
        std::cout << "   Error: Should have thrown exception\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "   Successfully caught exception: " << e.what() << std::endl;
    }
}

// d) Test Queue implementation using Priority Queue
void testQueueImplementation() {
    std::cout << "\n=== Test Queue Implementation (FIFO using Priority Queue) ===\n";
    
    Queue queue;
    std::cout << "1. Test empty queue:\n";
    std::cout << "   Queue is empty: " << (queue.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "   Enqueuing: 10\n";
	queue.enqueue(10);
	std::cout << "   Queue is empty: " << (queue.isEmpty() ? "true" : "false") << std::endl;
	queue.dequeue();

    std::cout << "\n2. Test enqueue operation:\n";
    std::cout << "   Enqueuing: 1, 2, 3, 4\n";
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);

    std::cout << "\n3. Test dequeue operation (should be FIFO order):\n";
    std::cout << "   Expected order: 1, 2, 3, 4\n";
    std::cout << "   Actual order:\n";
    while (!queue.isEmpty()) {
        std::cout << "   Dequeued: " << queue.dequeue() << std::endl;
    }

    std::cout << "\n4. Test empty queue operations:\n";
    std::cout << "   Queue is empty: " << (queue.isEmpty() ? "true" : "false") << std::endl;
    
    std::cout << "\n5. Test exception on empty queue:\n";
    try {
        queue.dequeue();
        std::cout << "   Error: Should have thrown exception\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "   Successfully caught exception: " << e.what() << std::endl;
    }

    std::cout << "\n6. Test mixed operations:\n";
    std::cout << "   Enqueuing: 10\n";
    queue.enqueue(10);
    std::cout << "   Enqueuing: 20\n";
    queue.enqueue(20);
    std::cout << "   Dequeuing: " << queue.dequeue() << std::endl;
    std::cout << "   Enqueuing: 30\n";
    queue.enqueue(30);
    std::cout << "   Remaining elements (should be 20, 30):\n";
    while (!queue.isEmpty()) {
        std::cout << "   Dequeued: " << queue.dequeue() << std::endl;
    }
}
