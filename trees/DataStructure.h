#ifndef DATA_STRUCTURES_ASS2_DATASTRUCTURE_H
#define DATA_STRUCTURES_ASS2_DATASTRUCTURE_H

#include <bits/stdc++.h>
#include "Item.h"
using namespace std;

class DataStructure{
public:
    virtual void add(Item &item) = 0;
    virtual bool remove(Item item) = 0;
    virtual void print() = 0;
    virtual void printSmaller() = 0;
    virtual void printLarger() = 0;
};

#endif //DATA_STRUCTURES_ASS2_DATASTRUCTURE_H
