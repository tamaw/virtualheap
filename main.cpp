#include <iostream> // cout, endl
#include <climits>  // MAX, MIN contants
#include <cassert> // assert macro
#include "mem_heap.h"

using namespace std;

int main()
{
    MemHeap mheap;

    cout << "Testing vheap. All values are tested with asserts.\n\n";

    // Allocate some common datatypes.
    cout << "Allocate some common datatypes.\n";
    int* myInt = (int*)mheap.vnew(sizeof(int));
    long* myLong = (long*)mheap.vnew(sizeof(long));
    char* myCharArray = (char*)mheap.vnew(sizeof(char) * 2);

    // Assign and test values.
    cout << "Assign and test values.\n";
    *myInt = INT_MAX;
    *myLong = LONG_MAX;
    myCharArray[0] = CHAR_MAX;
    myCharArray[1] = CHAR_MIN;

    assert(*myInt == INT_MAX);
    assert(*myLong == LONG_MAX);
    assert(myCharArray[0] == CHAR_MAX);
    assert(myCharArray[1] == CHAR_MIN);

    mheap.printHeapState();

    // Check the size is reported correctly
    assert(mheap.vsizeof(myInt) == sizeof(int));
    assert(mheap.vsizeof(myLong) == sizeof(long));

    // A request is too large for the heap.
    void* tooLarge = mheap.vnew(40000);
    assert(tooLarge == NULL);

    // Delete first.
    cout << "Delete first.\n";
    mheap.vdelete(myInt);
    mheap.printHeapState();

    // Reallocate and zero out a free node.
    cout << "Reallocate and zero out a free node.\n";
    myInt = (int*)mheap.vcnew(sizeof(int)); ///eek
    assert(*myInt == 0);
    mheap.printHeapState();

    // Clear heap.
    cout << "Clear heap.\n";
    mheap.vdelete(myInt);
    mheap.vdelete(myLong);
    mheap.vdelete(myCharArray);
    mheap.printHeapState();

    // Create some larger values.
    cout << "Create some larger values.\n";
    void* blocka = mheap.vnew(20);
    void* blockb = mheap.vnew(20);
    void* blockc = mheap.vnew(20);
    mheap.printHeapState();

    // Middle merge left.
    cout << "Middle merge left.\n";
    mheap.vdelete(blocka);
    mheap.vdelete(blockb);
    mheap.printHeapState();

    // Reset.
    cout << "Reset.\n";
    blocka = mheap.vnew(20);
    blockb = mheap.vnew(20);
    mheap.printHeapState();

    // Middle merge right.
    cout << "Middle merge right.\n";
    mheap.vdelete(blockc);
    mheap.vdelete(blockb);
    mheap.printHeapState();

    // Reset even larger values.
    cout << "Reset larger values.\n";
    mheap.vdelete(blocka);
    blocka = mheap.vnew(300);
    blockb = mheap.vnew(300);
    blockc = mheap.vnew(300);
    mheap.printHeapState();

    // Merge all.
    cout << "Merge all.\n";
    mheap.vdelete(blockc);
    mheap.vdelete(blockb);
    mheap.vdelete(blocka);
    mheap.printHeapState();

    // Allocate an extra small block.
    cout << "Allocate an extra small block.\n";
    myInt = (int*)mheap.vcnew(sizeof(int));
    *myInt = INT_MIN;
    assert(*myInt == INT_MIN);
    mheap.printHeapState();

    // Fill the heap with values.
    cout << "Fill the heap with values.\n";
    void* tmp;
    void* prev;

    do {
        prev = tmp;
        tmp = mheap.vnew(100);
    } while(tmp);

    mheap.printHeapState();

    // Reallocate a value at the end of the heap.
    cout << "Reallocate a value at the end of the heap.\n";
    mheap.vdelete(prev);
    int* atEnd = (int*)mheap.vnew(sizeof(int));
    *atEnd = INT_MIN;
    assert(*myInt == INT_MIN);

    mheap.printHeapState();

    return 0;
}

