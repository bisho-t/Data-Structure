#include <bits/stdc++.h>
using namespace std;

template<class elementType>
class CircularLinkedList {
private:
    struct node {
        elementType item;
        node* next;
    };

    node* first;
    node* last;
    int length;

public:
    CircularLinkedList(const CircularLinkedList&) = delete;
    CircularLinkedList& operator=(const CircularLinkedList& another) = delete;

    CircularLinkedList() {
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    ~CircularLinkedList() {
        clear();
    }

    void insertAtHead(elementType newitem) {
        node* newiemptr = new node;
        if (newiemptr == nullptr) {
            cout << "List cannot allocate memory." << endl;
            return;
        }
        newiemptr->item = newitem;

        if (isEmpty()) {
            first = last = newiemptr;
            newiemptr->next = first;
        } else {
            newiemptr->next = first;
            first = newiemptr;
            last->next = first;
        }
        length++;
    }

    void insertAtTail(elementType newitem) {
        node* newiemptr = new node;
        if (newiemptr == nullptr) {
            cout << "List cannot allocate memory." << endl;
            return;
        }
        newiemptr->item = newitem;

        if (isEmpty()) {
            first = last = newiemptr;
            newiemptr->next = first;
        } else {
            last->next = newiemptr;
            last = newiemptr;
            last->next = first;
        }
        length++;
    }

    void insertAt(elementType newitem, int index) {
        if (index < 0 || index > length) {
            cout << "Out of Range." << endl;
            return;
        }

        if (index == 0) {
            insertAtHead(newitem);
            return;
        }

        if (index == length) {
            insertAtTail(newitem);
            return;
        }

        node* newiemptr = new node;
        if (newiemptr == nullptr) {
            cout << "List cannot allocate memory." << endl;
            return;
        }

        newiemptr->item = newitem;
        node* current = get_nth(index - 1);
        newiemptr->next = current->next;
        current->next = newiemptr;

        length++;
    }

    void removeAtHead() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        node* temp = first;
        if (first == last) {
            first = last = nullptr;
        } else {
            first = first->next;
            last->next = first;
        }

        delete temp;
        length--;
    }

    void removeAtTail() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        if (first == last) {
            removeAtHead();
            return;
        }

        node* prev = get_nth(length - 2);
        delete last;
        last = prev;
        last->next = first;
        length--;
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

        node* prev = get_nth(index - 1);
        node* current = prev->next;

        prev->next = current->next;
        delete current;

        length--;
    }

    elementType retriveAt(int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return elementType();
        }

        node* current = get_nth(index);
        return current->item;
    }

    void replaceAt(elementType newElement, int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return;
        }

        node* current = get_nth(index);
        current->item = newElement;
    }

    bool isExist(elementType element) {
        node* current = first;
        do {
            if (current->item == element) {
                return true;
            }
            current = current->next;
        } while (current != first);

        return false;
    }

    bool isItemAtEqual(elementType element, int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return false;
        }

        node* current = get_nth(index);
        return current->item == element;
    }

    void swap(int firstItemIndex, int secondItemIndex) {
        if (firstItemIndex == secondItemIndex || firstItemIndex < 0 || secondItemIndex < 0 ||
            firstItemIndex >= length || secondItemIndex >= length) {
            cout << "Out of range" << endl;
            return;
        }

        if(firstItemIndex == secondItemIndex)
            return;

        if (firstItemIndex > secondItemIndex)
            swap(firstItemIndex, secondItemIndex);

        node* prevFirst;
        node* First;
        node* prevSecond;
        node* Second;
        if(firstItemIndex == 0){
            prevFirst = nullptr;
            First = first;
        }else{
            prevFirst = get_nth(firstItemIndex-1);
            First = prevFirst->next;
        }
        prevSecond = get_nth(secondItemIndex-1);
        Second = prevSecond->next;

        if (prevSecond == First) {
            First->next = Second->next;
            Second->next = First;
            if (prevFirst) {
                prevFirst->next = Second;
            } else {
                first = Second;
                last->next = Second;
            }
            if (secondItemIndex == length-1) {
                last = First;
                First->next = first;
            }
        } else {
            if (prevFirst) {
                prevFirst->next = Second;
            } else {
                first = Second;
                last->next = Second;
            }

            prevSecond->next = First;

            node *temp = Second->next;
            Second->next = First->next;
            First->next = temp;

            if (secondItemIndex == length-1) {
                last = First;
                First->next = first;
            }
        }
    }

    bool isEmpty() {
        return length == 0;
    }

    int linkedListSize() {
        return length;
    }

    void clear() {
        while (!isEmpty()) {
            removeAtHead();
        }
    }

    void print() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        node* current = first;
        do {
            cout << current->item << " ";
            current = current->next;
        } while (current != first);

        cout << endl;
    }

private:
    node* get_nth(int index) {
        if (index < 0 || index >= length) {
            cout << "Out of Range." << endl;
            return nullptr;
        }

        node* current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
    }
};

int main() {
    CircularLinkedList<int> lst;
    lst.insertAtTail(5);
    lst.insertAtHead(6);
    lst.insertAt(1, 1);
    lst.swap(0, 2);
    lst.insertAtTail(4);
    lst.print();
    return 0;
}
