#include <iostream>
#include <climits>
using namespace std;

class MinHeap {
public:
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

    // Constructor
    MinHeap(int cap) {
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];
    }

    // to get index of parent of node
    int parent(int i) {
        return (i - 1) / 2;
    }

    // to get index of left child of node
    int left(int i) {
        return (2 * i + 1);
    }

    // to get index of right child of node
    int right(int i) {
        return (2 * i + 2);
    }

    // to heapify a subtree with the root at given index
    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && harr[l] < harr[smallest])
            smallest = l;

        if (r < heap_size && harr[r] < harr[smallest])
            smallest = r;

        if (smallest != i) {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }

    // utility function swap
    void swap(int *x, int *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    // Extract the minimum element (root of the heap)
    int extractMin() {
        if (heap_size <= 0)
            return INT_MAX;

        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }

        // Store the minimum value, and remove it from the heap
        int root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // Get the minimum key (key at root) from the heap
    int getMin() {
        return harr[0];
    }

    // Deletes a key
    void deleteKey(int i) {
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    // Inserts a new key
    void insertKey(int key) {
        if (heap_size == capacity) {
            cout << "Overflow: Could not insert key" << endl;
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = key;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    // Decrease the value of a key
    void decreaseKey(int i, int new_val) {
        harr[i] = new_val;
        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
};

// Function to validate the MinHeap implementation
void testMinHeap() {
    MinHeap heap(11);
    
    heap.insertKey(3);
    heap.insertKey(2);
    heap.deleteKey(1);
    heap.insertKey(15);
    heap.insertKey(5);
    heap.insertKey(4);
    heap.insertKey(45);

    cout << "Extracted Min: " << heap.extractMin() << endl;
    cout << "Current Min: " << heap.getMin() << endl;

    heap.deleteKey(2);
    cout << "Extracted Min: " << heap.extractMin() << endl;
    cout << "Current Min: " << heap.getMin() << endl;
}

int main() {
    testMinHeap();
    return 0;
}

