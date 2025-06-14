#include <bits/stdc++.h>
using namespace std;

template<class elementType>
class LinkedList{
private:
    struct node{
        elementType item;
        node* next;
    };
    node* first, *last;
    int length;

public:
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList& another) = delete;

    LinkedList(){
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    ~LinkedList(){
        while(first!=NULL){
            node *temp = first;
            first = first->next;
            temp = temp->next = NULL;
            delete temp;
        }
        delete first;
        delete last;
    }

    void insertAtHead(elementType newitem){
        node *newiemptr = new node;
        if(newiemptr == NULL){
            cout << "List can not allocate memory." << endl;
            return;
        }
        newiemptr->item = newitem;
        newiemptr->next = first;
        if(!length){
            first = last = newiemptr;
            newiemptr->next = NULL;
            length++;
            return;
        }
        first = newiemptr;
        length++;
    }

    void insertAtTail(elementType newitem){
        node *newiemptr = new node;
        if(newiemptr == NULL){
            cout << "List can not allocate memory." << endl;
            return;
        }
        newiemptr->item = newitem;
        newiemptr->next = NULL;
        if(!length){
            first = last = newiemptr;
            length++;
            return;
        }
        last->next = newiemptr;
        last = newiemptr;
        length++;
    }

    void insertAt(elementType newitem, int index){
        if(index < 0 || index > length){
            cout << "Out of Range." << endl;
            return;
        }

        if(index == 0){
            insertAtHead(newitem);
            return;
        }
        if(index == length){
            insertAtTail(newitem);
            return;
        }
        node *newiemptr = new node;
        if(newiemptr == NULL){
            cout << "List can not allocate memory." << endl;
            return;
        }
        newiemptr->item = newitem;
        node* current = get_nth(index-1);
        newiemptr->next = current->next;
        current->next = newiemptr;
        length++;
    }

    void removeAtHead(){
        if(!length){
            cout << "List is empty." << endl;
            return;
        }
        node *temp = first;
        first = first->next;
        temp->next = nullptr;
        if(!first)
            last = nullptr;
        length--;
        delete temp;
    }

    void removeAtTail(){
        if(length <= 1) {
            removeAtHead();
            return;
        }
        node *prev = get_nth(length-2);
        delete last;
        last = prev;
        last->next = nullptr;
        length--;
    }

    void removeAt(int idx){
        if(idx < 0 || idx >= length){
            cout << "Out of Range." << endl;
            return;
        }
        if(idx==0){
            removeAtHead();
            return;
        }
        if(idx==length-1){
            removeAtTail();
            return;
        }
        node *prev = get_nth(idx-1);
        node *nth = prev->next;
        prev->next = nth->next;
        nth->next = nullptr;
        length--;
        prev = nullptr;
        delete prev;
        delete nth;
    }

    elementType retriveAt(int idx){
        if(idx < 0 || idx >= length){
            cout << "Out of Range." << endl;
            return nullptr;
        }
        int cnt = 0;
        node *temp = first;
        while(temp!=nullptr){
            if(cnt==idx)
                return temp->item;
            temp = temp->next;
            cnt++;
        }
    }

    void replaceAt(elementType newElement, int idx){
        if(idx < 0 || idx >= length){
            cout << "Out of Range." << endl;
            return;
        }
        int cnt = 0;
        node *temp = first;
        while(temp!=nullptr){
            if(cnt==idx){
                temp->item = newElement;
                return;
            }
            temp = temp->next;
            cnt++;
        }
    }

    bool isExist(elementType element){
        int cnt = 0;
        node temp = first;
        while(temp!=nullptr){
            if(temp->item == element)
                return true;
            temp = temp->next;
            cnt++;
        }
        return false;
    }

    bool isItemAtEqual(elementType element, int idx){
        if(idx < 0 || idx >= length){
            cout << "Out of Range." << endl;
            return false;
        }
        int cnt = 0;
        node *temp = first;
        while(temp!=nullptr){
            if(cnt==idx)
                return temp->item == element;
            temp = temp->next;
            cnt++;
        }
    }

    void swap(int firstItemIndex, int secondItemIndex){
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
            }
            if (First->next == nullptr) {
                last = First;
            }
        } else {
            if (prevFirst) {
                prevFirst->next = Second;
            } else {
                first = Second;
            }

            prevSecond->next = First;

            node *temp = Second->next;
            Second->next = First->next;
            First->next = temp;

            if (First->next == nullptr) {
                last = First;
            }
            if (Second->next == nullptr) {
                last = Second;
            }
        }
    }

    bool isEmpty(){
        return length == 0;
    }

    int linkedListSize(){
        return length;
    }

    void clear(){
        while(first!=NULL){
            node *temp = first;
            first = first->next;
            temp = temp->next = NULL;
            delete temp;
        }
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    void print(){
        node* cur = first;
        while(cur!=NULL){
            cout << cur->item << " ";
            cur = cur->next;
        }
        cout << endl;
        cur = NULL;
        delete cur;
        return;
    }
private:
    node* get_nth(int idx){
        if(idx < 0 || idx >= length){
            cout << "Out of Range." << endl;
            return nullptr;
        }
        int cnt = 0;
        node *temp = first;
        while(temp!=nullptr){
            if(cnt==idx)
                return temp;
            temp = temp->next;
            cnt++;
        }
    }
};

int main() {
    LinkedList<int> lst;
    lst.insertAtTail(5);
    lst.insertAtHead(6);
    lst.insertAt(1, 1);
    lst.swap(1, 2);
    lst.insertAtTail(4);
    lst.print();
    return 0;
}