cmake_minimum_required(VERSION 3.29)
project(data_structure)

set(CMAKE_CXX_STANDARD 14)

add_executable(Circular_Linked_List Linked_List/Circular_Linked_List.cpp)
add_executable(Doubly_Linked_List Linked_List/Doubly_Linked_List.cpp)
add_executable(Queue queue/Queue.cpp)
add_executable(Singly_Linked_List Linked_List/Singly_Linked_List.cpp)
add_executable(Sorting_Algorithms Sorting_Algorithms.cpp)
add_executable(stack stack/Stack.cpp)
add_executable(trees
        trees/AVL.h
        trees/BST.h
        trees/DataStructure.h
        trees/Item.h
        trees/main.cpp
        trees/Heap/MaxHeap.h
        trees/Heap/MinHeap.h
)
add_executable(RBtree trees/Red_Black_tree/RBtree.cpp
        trees/Red_Black_tree/RedBlackTree.h
        trees/Red_Black_tree/RedBlackTree.cpp)

