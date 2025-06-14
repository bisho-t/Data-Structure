cmake_minimum_required(VERSION 3.29)
project(trees)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(trees
    AVL.h
    BST.h
    DataStructure.h
    Item.h
    main.cpp
        Heap/MaxHeap.h
        Heap/MinHeap.h
        )
add_executable(RBtree Red_Black_tree/RBtree.cpp
Red_Black_tree/RedBlackTree.h
        Red_Black_tree/RedBlackTree.cpp)
