#ifndef DATA_STRUCTURES_ASS2_ITEM_H
#define DATA_STRUCTURES_ASS2_ITEM_H
#include <bits/stdc++.h>
using namespace std;
bool compare;

class Item{
    string itemname;
    string category;
    int price;
public:
    Item(){}
    Item(string name, string category, int price){
        this->itemname = name;
        this->category = category;
        this->price = price;
    }
    bool operator < (const Item &other){
        if(compare)
            return this->itemname < other.itemname;
        else
            return this->price < other.price;
    }

    bool operator > (const Item &other){
        if(compare)
            return this->itemname > other.itemname;
        else
            return this->price > other.price;
    }

    bool operator == (const Item &other){
        return ((this->itemname == other.itemname) && (this->category == other.category) && (this->price == other.price));
    }

    bool operator != (const Item &other){
        return this->itemname != other.itemname || this->category != other.category || this->price != other.price;
    }

    void print(){
        cout << "Name: " << itemname << endl;
        cout << "Category: " << category << endl;
        cout << "Price: " << price << endl;
        cout << endl;
    }
};

#endif //DATA_STRUCTURES_ASS2_ITEM_H
