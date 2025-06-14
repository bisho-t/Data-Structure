#include <bits/stdc++.h>
using namespace std;

template<class elementType>
class Stack{
private:
    struct node{
        elementType item;
        node* next;
    };
    node* first, *last;
    int length;
public:
    Stack(){
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    ~Stack(){
        while(first!=NULL){
            node *temp = first;
            first = first->next;
            temp = temp->next = NULL;
            delete temp;
        }
        delete first;
        delete last;
    }

    void push(elementType element){
        node *newiemptr = new node;
        if(newiemptr == NULL){
            cout << "List can not allocate memory." << endl;
            return;
        }
        newiemptr->item = element;
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

    elementType pop(){
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

    elementType top(){
        assert(!isEmpty());
        return first->item;
    }

    bool isEmpty(){
        return (length == 0);
    }

    int stackSize(){
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
    Stack<int> st;
    st.push(5);
    st.push(6);
    st.push(7);
    st.print();
    st.pop();
    st.push(10);
    st.print();
    cout << st.isEmpty() << endl;
    cout << st.stackSize() << endl;
    cout << st.top() << endl;
    st.clear();
    cout << st.isEmpty() << endl;
    return 0;
}
