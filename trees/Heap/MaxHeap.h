#ifndef DATA_STRUCTURES_ASS2_MAXHEAP_H
#define DATA_STRUCTURES_ASS2_MAXHEAP_H

#include <bits/stdc++.h>
#include "DataStructure.h"
#include "Item.h"
using namespace std;

class MaxHeap : public DataStructure {
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
        if (child_pos == 0 || array[par_pos] > array[child_pos])
            return;

        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int parent_pos) {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1)
            return;
        if (right_child != -1 && array[right_child] > array[child_pos])
            child_pos = right_child;

        if (array[parent_pos] < array[child_pos]) {
            swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    bool isempty() {
        return size == 0;
    }

    Item top() {
        if (isempty()) {
            cout << "Empty Heap." << endl;
            return Item("", "", 0);
        }
        return array[0];
    }

    void heapify(int n, int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l != -1 && l < n && array[l] > array[largest])
            largest = l;

        if (r != -1 && r < n && array[r] > array[largest])
            largest = r;

        if (largest != i) {
            swap(array[i], array[largest]);
            heapify(n, largest);
        }
    }

public:
    MaxHeap() {
        array = new Item[capacity] {};
        size = 0;
    }

    MaxHeap(vector<Item> &v) {
        array = new Item[capacity] {};
        size = v.size();
        for (int i = 0; i < size; ++i)
            array[i] = v[i];
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify_down(i);
    }

    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }

    void add(Item &key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    bool remove(Item key) {
        if (isempty()) {
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

    void printSmaller() {
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

    void printLarger() {
        vector<Item> v;
        int sz = size;
        for (int i = 0; i < sz; ++i) {
            Item tp = top();
            tp.print();
            v.push_back(tp);
            remove(tp);
        }
        for (int i = 0; i < sz; ++i) {
            add(v.back());
            v.pop_back();
        }
    }
};


#endif //DATA_STRUCTURES_ASS2_MAXHEAP_H
