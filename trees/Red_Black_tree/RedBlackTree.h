#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <iostream>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;

    explicit Node(T value) : data(value), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

template <typename T>
class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(T value);
    void deleteNode(T value);
    void printTree();

private:
    Node<T>* root;

    void rotateLeft(Node<T>* node);
    void rotateRight(Node<T>* node);
    void balanceAfterInsert(Node<T>* node);
    void balanceAfterDelete(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
    void deleteNodeHelper(Node<T>* node);
    void inorderTraversal(Node<T>* node);
    void deleteTree(Node<T>* node);
};

// Utility function for printing
template <typename T>
void printHelper(Node<T>* root, std::string indent, bool last);

#endif // RED_BLACK_TREE_H
