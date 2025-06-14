#ifndef DATA_STRUCTURES_ASS2_MINHEAP_H
#define DATA_STRUCTURES_ASS2_MINHEAP_H

#include <bits/stdc++.h>
#include "DataStructure.h"
#include "MaxHeap.h"
#include "Item.h"
using namespace std;

class MinHeap: public DataStructure{
private:
    Item *array { };
    int size { };
    int capacity { 1000 };

    int left(int node) {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }

    int right(int node) {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }

    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    void heapify_up(int child_pos) {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || array[par_pos] < array[child_pos])
            return;

        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int parent_pos) {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1)
            return;
        if (right_child != -1 && array[right_child] < array[child_pos])
            child_pos = right_child;

        if (array[parent_pos] > array[child_pos]) {
            swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    bool isempty() {
        return size == 0;
    }

    Item top() {
        if(isempty()){
            cout << "Empty Heap." << endl;
            return Item("", "", 0);
        }
        return array[0];
    }

    void heapify(int n, int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l != -1 && l < n && array[l] < array[smallest])
            smallest = l;

        if (r != -1 && r < n && array[r] < array[smallest])
            smallest = r;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapify(n, smallest);
        }
    }

public:
    MinHeap() {
        array = new Item[capacity] {};
        size = 0;
    }

    ~MinHeap() {
        delete[] array;
        array = nullptr;
    }

    void add(Item &key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    bool remove(Item key) {
        if(isempty()){
            cout << "Empty Heap." << endl;
            return false;
        }
        array[0] = array[--size];
        heapify_down(0);
        return true;
    }

    void print(){
        for (int i = 0; i < size; ++i)
            array[i].print();
    }

    void printSmaller(){
        vector<Item> v(size);
        for (int i = 0; i < size; ++i)
            v[i] = array[i];
        DataStructure *mxheap = new MaxHeap(v);
        mxheap->printSmaller();
        delete mxheap;
    }

    void printLarger(){
        Item arr[size];
        for (int i = 0; i < size; ++i)
            arr[i] = array[i];
        for (int i = size - 1; i >= 0; i--) {
            swap(array[0], array[i]);
            heapify(i, 0);
        }
        for (int i = 0; i < size; ++i)
            array[i].print();
        for (int i = 0; i < size; ++i)
            array[i] = arr[i];
    }
};


#endif //DATA_STRUCTURES_ASS2_MINHEAP_H
