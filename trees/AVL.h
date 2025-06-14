#ifndef DATA_STRUCTURES_ASS2_AVL_H
#define DATA_STRUCTURES_ASS2_AVL_H

#include <bits/stdc++.h>
#include "DataStructure.h"
#include "Item.h"
using namespace std;

class AVLTree: public DataStructure{
private:
    struct BinaryNode {
        Item data;
        int height{};
        BinaryNode *left{};
        BinaryNode *right{};

        BinaryNode(Item &data) :
                data(data) {
        }

        int ch_height(BinaryNode *node) {
            if (!node)
                return -1;
            return node->height;
        }

        int update_height() {
            return height = 1 + max(ch_height(left), ch_height(right));
        }

        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };

    BinaryNode *root{};

    bool search(Item &target, BinaryNode *node) {
        if (!node)
            return false;

        if (target == node->data)
            return true;

        if (target < node->data)
            return search(target, node->left);

        return search(target, node->right);
    }

    BinaryNode *right_rotation(BinaryNode *Q) {
        BinaryNode *P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update_height();
        P->update_height();
        return P;
    }

    BinaryNode *left_rotation(BinaryNode *P) {
        BinaryNode *Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }

    BinaryNode* balance(BinaryNode* node) {
        if (node->balance_factor() == 2) {
            if (node->left->balance_factor() == -1)
                node->left = left_rotation(node->left);

            node = right_rotation(node);
        } else if (node->balance_factor() == -2) {
            if (node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);

            node = left_rotation(node);
        }
        return node;
    }

    BinaryNode* min_node(BinaryNode* cur) {
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }

    BinaryNode* insert_node(Item &target, BinaryNode* node) {
        if (target < node->data) {
            if (!node->left)
                node->left = new BinaryNode(target);
            else
                node->left = insert_node(target, node->left);
        } else if (target > node->data) {
            if (!node->right)
                node->right = new BinaryNode(target);
            else
                node->right = insert_node(target, node->right);
        }
        node->update_height();
        return balance(node);
    }

    BinaryNode* delete_node(Item &target, BinaryNode* node) {
        if (!node)
            return nullptr;

        if (target < node->data)
            node->left = delete_node(target, node->left);
        else if (target > node->data)
            node->right = delete_node(target, node->right);
        else {
            BinaryNode* tmp = node;

            if (!node->left && !node->right)
                node = nullptr;
            else if (!node->right)
                node = node->left;
            else if (!node->left)
                node = node->right;
            else {
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
                tmp = nullptr;
            }
            if (tmp)
                delete tmp;
        }
        if (node) {
            node->update_height();
            node = balance(node);
        }
        return node;
    }

    void print(BinaryNode* node){
        if(!node)
            return;
        node->data.print();
        print_inorder(node->left);
        print_inorder(node->right);
    }

    void print_inorder(BinaryNode* node) {
        if(!node)
            return;
        print_inorder(node->left);
        node->data.print();
        print_inorder(node->right);
    }

    void print_postorder(BinaryNode* node) {
        if(!node)
            return;
        print_postorder(node->right);
        node->data.print();
        print_postorder(node->left);
    }

public:
    AVLTree(){}

    AVLTree(Item &item){
        this->add(item);
    }

    void add(Item &target) {
        if (!root)
            root = new BinaryNode(target);
        else
            root = insert_node(target, root);
    }

    bool remove(Item target) {
        if(!search(target)){
            return false;
        }
        if (root) {
            root = delete_node(target, root);
        }else{
            return false;
        }
        return true;
    }

    bool search(Item &target) {
        return search(target, root);
    }

    void print(){
        print(root);
    }

    void printSmaller() {
        print_inorder(root);
    }

    void printLarger(){
        print_postorder(root);
    }
};


#endif //DATA_STRUCTURES_ASS2_AVL_H
