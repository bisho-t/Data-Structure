#include <iostream>
#include"RedBlackTree.h"
int main()
{
    RedBlackTree<int> t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(10);
    t.insert(90);
    t.insert(16);
    t.insert(100);
    t.insert(-50);
    t.insert(24);
    t.insert(63);
    t.insert(92);

    t.printTree();

    t.deleteNode(63);
    t.printTree();

    t.deleteNode(30);
    t.deleteNode(70);
    t.deleteNode(10);
    t.deleteNode(90);
    t.deleteNode(16);
    t.deleteNode(100);
    t.deleteNode(-50);
    t.deleteNode(24);
    t.deleteNode(63);
    t.deleteNode(90);
    t.printTree();
}
