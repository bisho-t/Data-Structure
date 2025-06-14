#include <bits/stdc++.h>
using namespace std;

template<class elementType>
class Queue{
private:
    struct node{
        elementType item;
        node* next;
    };
    node* first, *last;
    int length;
public:
    Queue(){
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    ~Queue(){
        while(first!=NULL){
            node *temp = first;
            first = first->next;
            temp = temp->next = NULL;
            delete temp;
        }
        delete first;
        delete last;
    }

    void enqueue(elementType element){
        node *newiemptr = new node;
        if(newiemptr == NULL){
            cout << "List can not allocate memory." << endl;
            return;
        }
        newiemptr->item = element;
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

    elementType dequeue(){
        assert(!isEmpty());
        node *temp = first;
        int value = first->item;
        first = first->next;
        temp->next = nullptr;
        if(!first)
            last = nullptr;
        length--;
        delete temp;
        return value;
    }

    elementType firstElement(){
        assert(!isEmpty());
        return first->item;
    }

    bool isEmpty(){
        return length == 0;
    }

    int queueSize(){
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
};

int main() {
    Queue<int> que;
    que.enqueue(4);
    que.enqueue(6);
    que.enqueue(8);
    que.enqueue(10);
    que.enqueue(12);
    que.print();
    que.dequeue();
    cout << que.firstElement() << endl;
    que.dequeue();
    que.print();
    que.dequeue();
    que.dequeue();
    que.dequeue();
    que.firstElement();
    cout << que.isEmpty() << endl;
    return 0;
}
