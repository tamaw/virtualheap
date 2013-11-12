#include <iostream>  // cout, endl
#include <cstring> // memset
#include "mem_heap.h"

/*
 * Allocate memory on the heap.
 * 
 * Parameter size - The number of bytes for the memory block
 * Return - A pointer to the memory block
 */
void* MemHeap::vnew(size_t size) 
{
    Node* mem = 0;
    Node* tmp = (Node*)vheap;
    int existingSize = 0;

    // Check if any existing nodes can be used.
    while(tmp && tmp != tail) { 
        existingSize = tmp->size;

        if(!tmp->used && tmp->size >= size) {
            mem = tmp;
            break;
        }
        tmp = tmp->next;
    }

    if(tmp == tail && tail->size >= size + sizeof(Node)) {
        existingSize = 0; // No longer care for the existingSize.
        mem = tail;

        // New empty tail node.
        tmp = (Node*)((char*)tail + sizeof(Node) + size);
        tmp->size = tail->size - (sizeof(Node) + size);
        tmp->used = false;
        tmp->next = 0;

        // Update tail to the new end.
        tail->next = tmp;
        tail = tmp;
    }

    if(!mem)
        return 0; // Cannot satisfy request.
    
    // Use the greater existing size of the node so we don't lose space!
    mem->size = (existingSize > size) ? existingSize : size;
    mem->used = true;

    return (char*)mem + sizeof(Node);
}

/*
 * Allocate an empty block of memory.
 *
 * Parameter size - The number of bytes for the memory block
 * Return - A pointer to the memory block
 */
void* MemHeap::vcnew(size_t size) 
{
    void* mem = vnew(size);
    memset(mem, 0, size);
    return mem;
}

/*
 * Return an allocated memory block back to the heap for use later
 *
 * Parameter mem - The address to the memory block
 */
void MemHeap::vdelete(void* mem) 
{
    Node* memNode = (Node*)((char*)mem - sizeof(Node));
    Node* tmp = (Node*)vheap;
    Node* prev = NULL;
    Node* next = NULL;

    // Find the previous and next node
    while(tmp && tmp != memNode) {
        prev = tmp;
        tmp = tmp->next;
    }

    if(!tmp) return; // The memory address was not found.

    next = tmp->next;
    memNode->used = false;

    // Merge the previous node.
    if(prev && !prev->used) {
        prev->size += sizeof(Node) + memNode->size;
        prev->next = next;
        memNode = prev;

        if(memNode == tail)
            tail = prev;
    }

    // Merge the next node.
    if(next && !next->used) {
        memNode->size += sizeof(Node) + next->size;
        memNode->next = next->next;

        if(next == tail) 
            tail = memNode;
    }
}

/*
 * Get the size of a memory block.
 * 
 * Parameter mem - The address to the memory block
 * Return - Size of the memory block
 */
size_t MemHeap::vsizeof(void* mem) 
{
    Node* tmp = (Node*)((char*)mem - sizeof(Node));
    return tmp->size;
}

/*
 * Display the current status of the heap. Each byte is represented by either an
 * I for information, D for data or F for free bytes. 
 */
void MemHeap::printHeapState() 
{
    using namespace std;

    Node* tmp = (Node*)vheap;

    // Advance to each node and output its status.
    while(tmp) {
        for(int i = 0; i < sizeof(Node); i++)
            cout << 'I';

        for(int i = 0; i < tmp->size; i++)
            cout << ((tmp->used) ? 'D' : 'F');

        tmp = tmp->next;
    }

    cout << endl << endl;
}

