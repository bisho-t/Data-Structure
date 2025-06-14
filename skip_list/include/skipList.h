#ifndef SKIPLIST_H
#define SKIPLIST_H
#include<iostream>
#include<vector>
#include<random>
using namespace std;

class skipNode
{
public:
    int key;
    int value;
    vector<skipNode*> next{};
    skipNode(int key, int value ,  int level): key(key) , value(value), next(level + 1 , nullptr){}

};

class skipList {
    skipNode* head;
    int level;
    int size;
    mt19937 generator;
    uniform_int_distribution<int> distribution;
public:

    skipList();
    void insert(int comparableKey , int value);
    [[nodiscard]] bool search(int key) const;
    void remove (int key);
    void display() const;
    [[nodiscard]] skipNode* getHead() const;
    [[nodiscard]] int getLevel()  const;
    ~skipList();


};

#endif SKIPLIST_H
