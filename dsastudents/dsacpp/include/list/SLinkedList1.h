#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H
#include "list/IList.h"
#include <memory.h>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template<class T>
class SLinkedList: IList<T> {
public:
    class Iterator; //forward declaration
    class Node;
protected:
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);      //function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(SLinkedList<T>*); //function pointer: be called to remove items (if they are pointer type)
    Node *head;
public:
    SLinkedList(
            void (*deleteUserData)(SLinkedList<T>*)=0, 
            bool (*itemEqual)(T&, T&)=0 );
    SLinkedList(const SLinkedList<T>& list);
    SLinkedList<T>& operator=(const SLinkedList<T>& list);
    ~SLinkedList();
    
    //Inherit from IList: BEGIN
    void    add(T e);
    void    add(int index, T e);
    T       removeAt(int index);
    bool    removeItem(T item, void (*removeItemData)(T)=0);
    bool    empty();
    int     size();
    void    clear();
    T&      get(int index);
    int     indexOf(T item);
    bool    contains(T item);
    string  toString(string (*item2str)(T&)=0 );
    //Inherit from IList: BEGIN
    
    
    void    println(string (*item2str)(T&)=0 ){
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(SLinkedList<T>*) = 0){
        this->deleteUserData = deleteUserData;
    }
    
    Iterator begin(){
        return Iterator(this, 0);
    }
    Iterator end(){
        return Iterator(this, count);
    }
public:
    class Node{
    private:
        T data;
        Node *next;
    public:
        Node(){
            this->next = NULL;
        }
        Node(T data){
            this->data = data;
            this->next = NULL;
        }
        ~Node();
    };

    class Iterator{
    private:
        Node* pNode;
        int index;
    public:
        Iterator(Node *pNode = NULL, bool begin = true){

        }
    };

};

//////////////////////////////////////////////////////////////////////
//////////////////////// *    METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

//? insert at the end 
template<class T>
void SLinkedList<T>::add(T e){
    Node *newNode = new Node(e);
    if(empty()){
        head = newNode;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    return;
}

template<class T>
void SLinkedList<T>::add(int index, T e){
    Node *newNode = new Node(e);
    if(empty()){
        head = newNode;
        return;
    }
    
}

//YOUR CODE HERE
    // bool found = false;
    // bool del= false;
    // Node* pNode = head->next;
    // Node* pPrev = head;
    // while(pNode != tail){
    //     if(pNode->data == item) found = true;
    //     if(found)
    //     {
    //         pPrev->next = pNode->next;
    //         if(pNode->next == tail) tail->next = pPrev;
    //         pNode->next = 0;

    //         if(removeItemData) removeItemData(pNode->data);
    //         this->count -= 1;
    //         delete pNode;
    //         del = true;
    //     }
    //     pNode = pNode->next;
    //     pPrev = pPrev->next;
    // }
    // if(del) return true;
    // return false;