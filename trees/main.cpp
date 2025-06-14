#include <bits/stdc++.h>
#include "Item.h"
#include "DataStructure.h"
#include "BST.h"
#include "AVL.h"
#include "heap/MinHeap.h"
#include "heap/MaxHeap.h"
using namespace std;

int readchoice(int low, int high){
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int choice; cin >> choice;

    if (low <= choice && choice <= high)
        return choice;

    cout << "Error: invalid number...Try again\n";
    return readchoice(low, high);
}

int readmenu(vector<string> menu){
    cout << endl;
    cout << "Menu" << endl;
    for (int i = 0; i < menu.size() ; ++i) {
        cout << "\t" << i+1 << "- " << menu[i] << endl;
    }
    return readchoice(1, menu.size());
}

void readItems(ifstream &inputFile, DataStructure* tree1, DataStructure* tree2){
    int numItems;
    inputFile >> numItems;
    for (int i = 0; i < numItems; ++i) {
        string name, category, line;
        int price;
        getline(inputFile, line);
        getline(inputFile, name);
        getline(inputFile, category);
        inputFile >> price;

        Item newItem(name, category, price);
        compare = true;
        tree1->add(newItem);
        compare = false;
        tree2->add(newItem);
    }
    cout << "Data collected successfully" << endl;
}


class Program{
    DataStructure *tree1;
    DataStructure *tree2;

public:
    ~Program(){
        delete tree1;
        delete tree2;
    }

    void run(){
        vector<string> menu;
        menu.push_back("Add item data");
        menu.push_back("Remove item data");
        menu.push_back("Display the item data normally");
        menu.push_back("Display all the items sorted by their name ascending");
        menu.push_back("Display all the items sorted by their name descending");
        menu.push_back("Display all the items sorted by their price ascending");
        menu.push_back("Display all the items sorted by their price descending");
        menu.push_back("Exit");
        while(true){
            int choice = readmenu(menu);
            if(choice == 1){
                string line;
                getline(cin, line);
                cout << "Enter item name: ";
                string name; getline(cin, name);
                cout << "Enter item category: ";
                string category; getline(cin, category);
                cout << "Enter item price: ";
                int price; cin >> price;

                Item newItem(name, category, price);
                compare = true;
                tree1->add(newItem);
                compare = false;
                tree2->add(newItem);
            }
            else if(choice == 2){
                string name = "";
                string category = "";
                int price = 0;

                if(typeid(*tree1) != typeid(MinHeap) && typeid(*tree1) != typeid(MaxHeap)){
                    cout << "Enter item name: ";
                    cin >> name;
                    cout << "Enter item category: ";
                    cin >> category;
                    cout << "Enter item price: ";
                    cin >> price;
                }
                Item newItem(name, category, price);
                compare = true;
                if(!tree1->remove(newItem)){
                    cout << "Item not found or there is only one element in the tree." << endl;
                    continue;
                }
                compare = false;
                tree2->remove(newItem);
            }
            else if(choice == 3){
                tree2->print();
            }
            else if(choice == 4){
                compare = true;
                tree1->printSmaller();
            }
            else if(choice == 5){
                compare = true;
                tree1->printLarger();
            }
            else if(choice == 6){
                compare = false;
                tree2->printSmaller();
            }
            else if(choice == 7){
                compare = false;
                tree2->printLarger();
            }
            else{
                return;
            }
        }
    }

    void start(){
        cout << "Welcome to our trees inventory!!" << endl;
        cout << "Choose your tree: " << endl;
        int choice = readmenu({"Binary Search Tree(BST)", "AVL Tree", "Heaps", "Exit"});
        if(choice == 1){
            tree1 = new BinarySearchTree();
            tree2 = new BinarySearchTree();
        } else if(choice == 2){
            tree1 = new AVLTree();
            tree2 = new AVLTree();
        } else if(choice == 3){
            tree1 = new MinHeap();
            tree2 = new MinHeap();
        } else{
            return;
        }
        cout << "Do you want to read items from file?" << endl;
        choice = readmenu({"Yes", "No"});
        if(choice == 1){
            cout << "Enter file name: ";
            string s; cin >> s;
            ifstream inputFile(s);
            if (!inputFile.is_open()) {
                cout << "Error opening file." << endl;
                return;
            }
            readItems(inputFile, tree1, tree2);
        }
        run();
    }
};

int main() {
    Program program;
    program.start();
    return 0;
}
