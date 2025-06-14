#include <iostream>
#include"skiplist.h"
using namespace std;

int main()
{
    skipList list;

    list.insert(20, 10);
    list.insert(20, 50);
    list.insert(41, 80);
    list.insert(6334, 85);
    list.insert(11478, 100);
    list.insert(15724, 5);
    list.insert(29358, 200);
    list.insert(26962, 180);
    list.insert(29358, -20);
    list.insert(26962, -50);
    list.insert(26962, 20);
    list.remove(50);
    list.remove(11478);
    list.display();
    return 0;
}