#ifndef MEMHEAP_H
#define MEMHEAP_H

#include "v_heap.h"

/**
 * MemHeap
 * 
 * Manages a virtual heap for allocating memory.
 */
class MemHeap : VHeap
{
private:
    struct Node {
        int size;
        bool used;
        Node* next;
    };

public:
    Node* tail;
    MemHeap() : VHeap()
    {
        tail = (Node*)vheap;
        tail->size = HEAP_SIZE - sizeof(Node);
        tail->used = false;
    }
    ~MemHeap() { }
    void* vnew(size_t size);
    void* vcnew(size_t size);
    void vdelete(void* mem);
    size_t vsizeof(void* mem);
    void printHeapState();
};

#endif // MEMHEAP_H

