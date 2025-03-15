#include <iostream>
#include "Test.h"

int main() {
    // a) Test Priority Queue implementation
    testPriorityQueueBasic();
    testPriorityQueueSamePriority();

    // b) Test sorting using Priority Queue
    testHeapSort();

    // c) Test Stack implementation using Priority Queue
    testStackImplementation();

    // d) Test Queue implementation using Priority Queue
    testQueueImplementation();

    return 0;
}