#include "RedBlackTree.h"


template <typename T>
RedBlackTree<T>::RedBlackTree() {
    root = nullptr;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    deleteTree(root);
}

template <typename T>
void RedBlackTree<T>::deleteTree(Node<T>* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename T>
void RedBlackTree<T>::rotateLeft(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node<T>* y) {
    Node<T>* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

template <typename T>
void RedBlackTree<T>::balanceAfterInsert(Node<T>* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node<T>* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else {
            Node<T>* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
template <typename T>
void RedBlackTree<T>::insert(T value)
    {
    // Check for duplicates before insertion
    Node<T>* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            std::cout << "Duplicate value " << value << " not inserted." << std::endl;
            return; // Exit without inserting
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Create the new node
    auto* node = new Node<T>(value);
    Node<T>* y = nullptr;
    Node<T>* x = root;

    // Standard BST insertion logic
    while (x != nullptr) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node; // Tree was empty
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    balanceAfterInsert(node);
}

template <typename T>
void RedBlackTree<T>::deleteNodeHelper(Node<T>* node) {
    if (node == nullptr) return;

    Node<T>* y = node;
    Node<T>* x = nullptr;
    Color originalColor = y->color;

    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    } else {
        y = node->right;
        while (y->left != nullptr) {
            y = y->left;
        }

        originalColor = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != nullptr) {
                x->parent = y;
            }
        } else {
            if(x != nullptr)
                x->parent = y ->parent;
            transplant(y, y->right);
            if (y->right != nullptr)
                y->right->parent = y;
            y->right = node->right;
            if (y->right != nullptr)
               y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        if (y->left != nullptr)
            y->left->parent = y;
        y->color = node->color;
    }

    if (originalColor == BLACK && x != nullptr) {
        balanceAfterDelete(x);
    }

    delete node;
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template <typename T>
void RedBlackTree<T>::balanceAfterDelete(Node<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node<T>* brother = x->parent->right;
            // Case 1: brother is red
            if (brother->color == RED) {
                brother->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                brother = x->parent->right;
            }
            // Case 2: brother and its children are black
            if ((brother->left == nullptr || brother->left->color == BLACK) &&
                (brother->right == nullptr || brother->right->color == BLACK)) {
                brother->color = RED;
                x = x->parent;
            } else {
                // Case 3: brother's right child is black, left child is red
                if (brother->right == nullptr || brother->right->color == BLACK) {
                    if (brother->left != nullptr) {
                        brother->left->color = BLACK;
                    }
                    brother->color = RED;
                    rotateRight(brother);
                    brother = x->parent->right;
                }
                // Case 4: Sibling's right child is red
                brother->color = x->parent->color;
                x->parent->color = BLACK;
                if (brother->right != nullptr) {
                    brother->right->color = BLACK;
                }
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            // Symmetric case: node is the right child

            Node<T>* w = x->parent->left;
            // Case 1: brother is red
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            // Case 2: brother and its children are black
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                // Case 3: brother's left child is black, right child is red
                if (w->left == nullptr || w->left->color == BLACK)
                {
                    if (w->right != nullptr) {
                        w->right->color = BLACK;
                    }
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                // Case 4: brother's left child is red
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr) {
                    w->left->color = BLACK;
                }
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}


template <typename T>
void RedBlackTree<T>::inorderTraversal(Node<T>* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

template <typename T>
void RedBlackTree<T>::deleteNode(T value) {
    Node<T>* node = root;
    while (node != nullptr) {
        if (node->data == value) {
            deleteNodeHelper(node);
            return;
        } else if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    std::cout << "Node with value " << value << " not found!" << std::endl;
}

template <typename T>
void RedBlackTree<T>::printTree() {
    printHelper(root, "", true);
}

// Helper function for printing the tree
template <typename T>
void printHelper(Node<T>* root, std::string indent, bool last) {
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string color = (root->color == RED) ? "RED" : "BLACK";
        std::cout << root->data << "(" << color << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

template class RedBlackTree<int>;
