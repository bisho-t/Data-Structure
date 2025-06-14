#include <bits/stdc++.h>
using namespace std;

template<class elementType>
class DoublyLinkedList {
private:
    struct node {
        elementType item;
        node* prev;
        node* next;
    };

    node* first;
    node* last;
    int length;

public:
    DoublyLinkedList() {
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    ~DoublyLinkedList() {
        clear();
    }

    void insertAtHead(elementType newItem) {
        node* newNode = new node{ newItem, nullptr, first };
        if (first) {
            first->prev = newNode;
        } else {
            last = newNode;
        }
        first = newNode;
        length++;
    }

    void insertAtTail(elementType newItem) {
        node* newNode = new node{ newItem, last, nullptr };
        if (last) {
            last->next = newNode;
        } else {
            first = newNode;
        }
        last = newNode;
        length++;
    }

    void insertAt(elementType newItem, int index) {
        if (index < 0 || index > length) {
            cout << "Out of Range." << endl;
            return;
        }

        if (index == 0) {
            insertAtHead(newItem);
            return;
        }

        if (index == length) {
            insertAtTail(newItem);
            return;
        }

        node* current = get_nth(index - 1);
        node* newNode = new node{ newItem, current, current->next };
        current->next->prev = newNode;
        current->next = newNode;
        length++;
    }

    void removeAtHead() {
        if (first == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        node* temp = first;
        first = first->next;
        if (first) {
            first->prev = nullptr;
        } else {
            last = nullptr;
        }
        length--;
        delete temp;
    }

    void removeAtTail() {
        if (last == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        node* temp = last;
        last = last->prev;
        if (last) {
            last->next = nullptr;
        } else {
            first = nullptr;
        }
        length--;
        delete temp;
    }

    void removeAt(int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return;
        }

        if (index == 0) {
            removeAtHead();
            return;
        }

        if (index == length - 1) {
            removeAtTail();
            return;
        }

        node* current = get_nth(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        length--;
    }

    elementType retrieveAt(int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return elementType();
        }

        node* current = get_nth(index);
        return current->item;
    }

    void replaceAt(elementType newItem, int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return;
        }

        node* current = get_nth(index);
        current->item = newItem;
    }

    bool isExist(elementType item) {
        node* current = first;
        while (current) {
            if (current->item == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isItemAtEqual(elementType item, int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return false;
        }

        node* current = get_nth(index);
        return current->item == item;
    }

    void swap(int firstItemIndex, int secondItemIndex) {
        if (firstItemIndex < 0 || secondItemIndex < 0 ||
            firstItemIndex >= length || secondItemIndex >= length) {
            cout << "Out of range" << endl;
            return;
        }

        if (firstItemIndex == secondItemIndex) {
            return;
        }

        node* firstNode = get_nth(firstItemIndex);
        node* secondNode = get_nth(secondItemIndex);

        if (firstNode->prev) {
            firstNode->prev->next = secondNode;
        } else {
            first = secondNode;
        }

        if (secondNode->prev) {
            secondNode->prev->next = firstNode;
        } else {
            first = firstNode;
        }

        if (firstNode->next) {
            firstNode->next->prev = secondNode;
        } else {
            last = secondNode;
        }

        if (secondNode->next) {
            secondNode->next->prev = firstNode;
        } else {
            last = firstNode;
        }

        node* tempPrev = firstNode->prev;
        firstNode->prev = secondNode->prev;
        secondNode->prev = tempPrev;

        node* tempNext = firstNode->next;
        firstNode->next = secondNode->next;
        secondNode->next = tempNext;
    }

    bool isEmpty() {
        return length == 0;
    }

    int linkedListSize() {
        return length;
    }

    void clear() {
        node* current = first;
        while (current) {
            node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    void print() {
        node* current = first;
        while (current) {
            cout << current->item << " ";
            current = current->next;
        }
        cout << endl;
    }

private:
    node* get_nth(int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return nullptr;
        }

        node* current = first;
        int cnt = 0;

        while (current && cnt < index) {
            current = current->next;
            cnt++;
        }

        return current;
    }
};

int main() {
    DoublyLinkedList<int> lst;
    lst.insertAtTail(5);
    lst.insertAtHead(6);
    lst.insertAt(1, 1);
    lst.swap(0, 1);
    lst.print();
    cout << lst.linkedListSize() << endl;
    return 0;
}
