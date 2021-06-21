/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedList.h
 * Author: LTSACH
 *
 * Created on 19 August 2020, 21:21
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;


template<class T>
class DLinkedList: IList<T> {
public:
    class Node; //Forward declaration
    class Iterator; //Forward declaration
    class BWDIterator; //Forward declaration
    
    /* The following is picture of double-linked list, there are three data members: head, tail, count
     
   (prev: # : next)<--->(prev: data: next)<--->(prev: data: next)<--->(prev: data: next)<--->(prev: # : next)
          ^                                                                                          ^
          |                                                                                          |
          |                                                                                          |
        head                                                                                        tail
        count: 3 (three nodes containing user's data)
     */
protected:
    Node *head; //this node does not contain user's data
    Node *tail; //this node does not contain user's data
    int count;
    bool (*itemEqual)(T& lhs, T& rhs); //function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(DLinkedList<T>*); //function pointer: be called to remove items (if they are pointer type)
    
public:
    DLinkedList(
            void (*deleteUserData)(DLinkedList<T>*)=0, 
            bool (*itemEqual)(T&, T&)=0); 
    DLinkedList(const DLinkedList<T>& list);
    DLinkedList<T>& operator=(const DLinkedList<T>& list);
    ~DLinkedList();
    
    
    //Inherit from IList: BEGIN
    void    add(T e);
    void    add(int index, T e);
    T       removeAt(int index);
    bool    removeItem(T item, void (*removeItemData)(T)=0);
    bool    empty();
    int      size();
    void    clear();
    T&      get(int index);
    int      indexOf(T item);
    bool    contains(T item);
    string  toString(string (*item2str)(T&)=0 );
    //Inherit from IList: END
    
    void    println(string (*item2str)(T&)=0 ){
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T>*) = 0){
        this->deleteUserData = deleteUserData;
    }
    
    bool contains(T array[], int size){
        int idx = 0;
        for(DLinkedList<T>::Iterator it = begin(); it != end(); it++){
            if(!equals(*it, array[idx++], this->itemEqual) ) return false;
        }
        return true;
    }
    
    /*
     * free(DLinkedList<T> *list):
     *  + to remove user's data (type T, must be a pointer type, e.g.: int*, Point*)
     *  + if users want a DLinkedList removing their data, 
     *      he/she must pass "free" to constructor of DLinkedList
     *      Example:
     *      DLinkedList<T> list(&DLinkedList<T>::free);
     */
    static void free(DLinkedList<T> *list){
        typename DLinkedList<T>::Iterator it = list->begin();
        while(it != list->end()){
            delete *it;
            it++;
        }
    }
    
    /* begin, end and Iterator helps user to traverse a list forwardly
     * Example: assume "list" is object of DLinkedList
     
     DLinkedList<char>::Iterator it;
     for(it = list.begin(); it != list.end(); it++){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    Iterator begin(){
        return Iterator(this, true);
    }
    Iterator end(){
        return Iterator(this, false);
    }
    
    
    /* last, beforeFirst and BWDIterator helps user to traverse a list backwardly
     * Example: assume "list" is object of DLinkedList
     
     DLinkedList<char>::BWDIterator it;
     for(it = list.last(); it != list.beforeFirst(); it--){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    BWDIterator bbegin(){
        return BWDIterator(this, true);
    }
    BWDIterator bend(){
        return BWDIterator(this, false);
    }
    
protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T& )){
        if(itemEqual == 0) return lhs == rhs;
        else return itemEqual(lhs, rhs);
    }
    void copyFrom(const DLinkedList<T>& list);
    void removeInternalData();
    Node* getPreviousNodeOf(int index);
    
//////////////////////////////////////////////////////////////////////
////////////////////////  INNER CLASSES DEFNITION ////////////////////
//////////////////////////////////////////////////////////////////////
public:
    
    class Node{
    public:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;
        
    public:
        Node(Node* next=0, Node* prev=0){
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node* next=0, Node* prev=0){
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
    
//////////////////////////////////////////////////////////////////////
    class Iterator{
    private:
        DLinkedList<T>* pList;
        Node* pNode;
        
    public:
        Iterator(DLinkedList<T>* pList=0, bool begin=true){
            if(begin){
                if(pList !=0) this->pNode = pList->head->next;
                else pNode = 0;
            }
            else{
                if(pList !=0) this->pNode = pList->tail;
                else pNode = 0;
            }
            this->pList = pList;
        }
        
        Iterator& operator=(const Iterator& iterator){
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T)=0){
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node* pNext = pNode->prev; //MUST prev, so iterator++ will go to end
            if(removeItemData != 0) removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }
        
        T& operator*(){
            return pNode->data;
        }
        bool operator!=(const Iterator& iterator){
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            pNode = pNode->next;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
    };
    
    //Backward Iterator
    class BWDIterator{
    private:
        DLinkedList<T>* pList;
        Node* pNode;
        
    public:
        BWDIterator(DLinkedList<T>* pList=0, bool last=true){
            if(last){
                if(pList !=0) this->pNode = pList->tail->prev;
                else pNode = 0;
            }
            else{
                if(pList !=0) this->pNode = pList->head;
                else pNode = 0;
            }
            this->pList = pList;
        }
        
        BWDIterator& operator=(const BWDIterator& iterator){
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T)=0){
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node* pNext = pNode->next; //MUST next, so iterator-- will go to head
            if(removeItemData != 0) removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }
        
        T& operator*(){
            return pNode->data;
        }
        bool operator!=(const BWDIterator& iterator){
            return pNode != iterator.pNode;
        }
        // Prefix -- overload 
        BWDIterator& operator--(){
            pNode = pNode->prev;
            return *this; 
        }
        // Postfix -- overload 
        BWDIterator operator--(int){
            BWDIterator iterator = *this; 
            --*this; 
            return iterator; 
        }
    };
    

};
//////////////////////////////////////////////////////////////////////
//Define a shorter name for DLinkedList:

template<class T>
using List = DLinkedList<T>;



//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
DLinkedList<T>::DLinkedList(
        void (*deleteUserData)(DLinkedList<T>*), 
        bool (*itemEqual)(T&, T&) ) {
    head = new Node();
    tail = new Node();
    head->next = tail; tail->next = 0;
    tail->prev = head; head->prev = 0;
    count = 0;
    this->itemEqual = itemEqual;
    this->deleteUserData = deleteUserData;
}

template<class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& list){
    //YOUR CODE HERE
    
    copyFrom(list);
}

template<class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& list){
    removeInternalData();
    copyFrom(list);
    
    return *this;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    removeInternalData();
    
    //YOUR CODE HERE
}

template<class T>
void DLinkedList<T>::add(T e) {
    Node* node = new Node(e, tail, tail->prev);
    //YOUR CODE HERE
}
template<class T>
void DLinkedList<T>::add(int index, T e) {
    if((index < 0) || (index > count))
        throw std::out_of_range("The index is out of range!");
    
    //YOUR CODE HERE
    
    //5. increase count by 1
    count += 1;
}

template<class T>
typename DLinkedList<T>::Node* DLinkedList<T>::getPreviousNodeOf(int index){
    Node* prevNode=0;
    int cursor;
    
    int mid = count/2;
    if(index < mid){
        //searching from: head
        prevNode = head;
        cursor = -1;
        while(cursor < index - 1){
            prevNode = prevNode->next;
            cursor += 1;
        }
    }
    else{
        //searching from: tail
        prevNode = tail;
        cursor = count;
        while(cursor >= index){
            prevNode = prevNode->prev;
            cursor -= 1;
        }
    }
    
    return prevNode;
}

template<class T>
T DLinkedList<T>::removeAt(int index){
    if((index < 0) || (index > count - 1))
        throw std::out_of_range("The index is out of range!");
    
    //YOUR CODE HERE
}

template<class T>
bool DLinkedList<T>::empty(){
    //YOUR CODE HERE
}

template<class T>
int  DLinkedList<T>::size(){
    //YOUR CODE HERE
}

template<class T>
void DLinkedList<T>::clear(){
    removeInternalData();
    
    //YOUR CODE HERE
}

template<class T>
T& DLinkedList<T>::get(int index){
    if((index < 0) || (index > count - 1))
        throw std::out_of_range("The index is out of range!");
    
    Node* prevNode = getPreviousNodeOf(index);
    
    //HERE: prevNode points to previous item (at index - 1); ready for get
    //YOUR CODE HERE
}

template<class T>
int  DLinkedList<T>::indexOf(T item){
    //YOUR CODE HERE
}

template<class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T)){
    //YOUR CODE HERE
}


template<class T>
bool DLinkedList<T>::contains(T item){
    //YOUR CODE HERE
}

template<class T>
string DLinkedList<T>::toString(string (*item2str)(T&) ){
    stringstream ss;
    ss << "[";
    Node* ptr = head->next;
    while(ptr != tail->prev){
        if(item2str != 0) ss << item2str(ptr->data) << ", ";
        else ss << ptr->data << ", ";
        
        ptr = ptr->next;
    }
    
    if(count > 0){
        if(item2str != 0) ss << item2str(ptr->data) << "]";
        else ss << ptr->data << "]";
    }
    else 
        ss << "]";
    return ss.str();
}


template<class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T>& list){
    //Initialize this list to the empty condition
    this->count = 0;
    this->head->next = this->tail; this->tail->next = 0;
    this->tail->prev = this->head; this->head->prev = 0;

    //Copy pointers from "list"
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;

    //Copy data from "list"
    Node* ptr= list.head->next;
    while(ptr != list.tail){
        this->add(ptr->data);
        ptr = ptr->next;
    }
}

template<class T>
void DLinkedList<T>::removeInternalData(){
    //Remove user's data stored in nodes
    if(deleteUserData != 0) deleteUserData(this);
    
    //Remove nodes
    if((head != 0) & (tail != 0)){
        Node* ptr = head->next;
        while(ptr != tail){
            Node* next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }
}


#endif /* DLINKEDLIST_H */

