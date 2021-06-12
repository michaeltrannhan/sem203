/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayList.h
 * Author: LTSACH
 *
 * Created on 13 August 2020, 14:09
 */

#ifndef XARRAYLIST_H
#define XARRAYLIST_H
#include "list/IList.h"
#include <memory.h>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template<class T>
class XArrayList: IList<T> {
public:
    class Iterator; //forward declaration
    
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int  count;      // number of items stored in the array
    bool (*itemEqual)(T& lhs, T& rhs);      //function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(XArrayList<T>*); //function pointer: be called to remove items (if they are pointer type)
    
public:
    XArrayList(
            void (*deleteUserData)(XArrayList<T>*)=0, 
            bool (*itemEqual)(T&, T&)=0 );
    XArrayList(const XArrayList<T>& list);
    XArrayList<T>& operator=(const XArrayList<T>& list);
    ~XArrayList();
    
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
    //Inherit from IList: BEGIN
    
    
    void    println(string (*item2str)(T&)=0 ){
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T>*) = 0){
        this->deleteUserData = deleteUserData;
    }
    
    Iterator begin(){
        return Iterator(this, 0);
    }
    Iterator end(){
        return Iterator(this, count);
    }
    
    /* if T is pointer type:
     *     pass THE address of method "free" to XArrayList<T>'s constructor:
     *     to:  remove the user's data (if needed)
     * Example:
     *  XArrayList<Point*> list(&XArrayList<Point*>::free);
     *  => Destructor will call free via function pointer "deleteUserData"
     */
    static void free(XArrayList<T> *list){
        typename XArrayList<T>::Iterator it = list->begin();
        while(it != list->end()){
            delete *it;
            it++;
        }
    }
protected:
    void checkIndex(int index); //check validity of index for accessing
    void ensureCapacity(int index); //auto-allocate if needed
    /* if T: primitive type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     * if T: object type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     *      Therefore, class of type T MUST override operator ==
     * if T: pointer type:
     *      indexOf, contains: will use function pointer "itemEqual"
     *      to: compare two items of T type
     *      Therefore:
     *      (1): must pass itemEqual to the constructor of XArrayList
     *      (2): must define a method for comparing 
     *           the content pointed by two pointers of type T
     *          See: definition of "equals" of class Point for more detail
     */
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T& )){
        if(itemEqual == 0) return lhs == rhs;
        else return itemEqual(lhs, rhs);
    }
    
    void copyFrom(const XArrayList<T>& list);
    void removeInternalData();
   
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public: 

    
    //Iterator: BEGIN
    class Iterator{
    private:
        int cursor;
        XArrayList<T>* pList;
    public:
        Iterator(XArrayList<T>* pList=0, int index=0){
            this->pList = pList;
            this->cursor = index;
        }
        Iterator& operator=(const Iterator& iterator){
            cursor = iterator.cursor;
            pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T)=0){
            T item = pList->removeAt(cursor);
            if(removeItemData != 0) removeItemData(item);
            cursor -= 1; //MUST keep index of previous, for ++ later
        }
        
        T& operator*(){
            return pList->data[cursor];
        }
        bool operator!=(const Iterator& iterator){
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            this->cursor++;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
    };
    //Iterator: END
};


//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
XArrayList<T>::XArrayList(
        void (*deleteUserData)(XArrayList<T>*), 
        bool (*itemEqual)(T&, T&) ) {
    capacity = 10; //initial size = 10; auto-inc if needed
    data = new T[capacity];
    count = 0;
    this->itemEqual = itemEqual;
    this->deleteUserData = deleteUserData;
}

template<class T>
void XArrayList<T>::copyFrom(const XArrayList<T>& list){
    //Initialize to the empty condition, with capacity = list.capacity
    capacity = list.capacity;
    data = new T[capacity];
    count = 0;
    
    //Copy pointers from "list"
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;

    //Copy data from "list"
    for(int idx=0; idx < list.count; idx++){
        this->add(list.data[idx]);
    }
}

template<class T>
void XArrayList<T>::removeInternalData(){
    //Remove pointers stored in the dynamic array (i.e., data)
    if(deleteUserData != 0) deleteUserData(this);
    
    //Remove the dynamic array
    if(data != 0) delete []data;
}
    
    
template<class T>
XArrayList<T>::XArrayList(const XArrayList<T>& list){
    copyFrom(list);
}

template<class T>
XArrayList<T>& XArrayList<T>::operator=(const XArrayList<T>& list){
    removeInternalData();
    copyFrom(list);
    
    return *this;
}

template<class T>
XArrayList<T>::~XArrayList() {
    removeInternalData();
}

template<class T>
void XArrayList<T>::add(T e) {
    ensureCapacity(count);
    
    data[count] = e;
    count += 1;
}
template<class T>
void XArrayList<T>::add(int index, T e) {
    ensureCapacity(index);

    for(int idx=count-1; idx >= index; idx-- ){
        data[idx + 1] = data[idx];
    }
    data[index] = e;
    count += 1;
}

template<class T>
T XArrayList<T>::removeAt(int index){
    checkIndex(index);
    
    T backup = this->data[index];
    //shift data to the left
    for(int idx=index; idx < count-1; idx++){
        this->data[idx] = this->data[idx+1];
    }
    this->count -= 1;
    return backup;
}

template<class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T)){
    bool found = false;
    int cursor = 0;
    while(cursor != count){
        found = XArrayList<T>::equals(this->data[cursor], item, this->itemEqual);
        if(found){
            //remove data at data[cursor]
            if(removeItemData) removeItemData(this->data[cursor]);
            //shift data
            for(int idx=cursor; idx < count-1; idx++){
                this->data[idx] = this->data[idx+1];
            }
            this->count -= 1;
            return true;
        }
        cursor++;
    }
    return false;
}

template<class T>
bool XArrayList<T>::empty(){
    return count == 0;
}

template<class T>
int  XArrayList<T>::size(){
    return count;
}

template<class T>
void XArrayList<T>::clear(){
    removeInternalData();
    
    //Put the list to the initial condition
    capacity = 10; //initial size = 10; auto-inc if needed
    data = new T[capacity];
    count = 0;
}

template<class T>
T& XArrayList<T>::get(int index){
    checkIndex(index);
    return data[index];
}

template<class T>
int  XArrayList<T>::indexOf(T item){
    bool found = false;
    int foundAt = -1;
    for(int idx=0; idx < count; idx++){
        found = XArrayList<T>::equals(data[idx], item, this->itemEqual);
        if(found){
            foundAt = idx;
            break;
        }
    }
    return foundAt;
}
template<class T>
bool XArrayList<T>::contains(T item){
    return indexOf(item) != -1;
}

template<class T>
string XArrayList<T>::toString(string (*item2str)(T&)){
    stringstream ss;
    ss << "[";
    for(int idx=0; idx < count-1; idx++){
        if(item2str != 0) ss << item2str(data[idx]) << ", ";
        else ss << data[idx] << ", ";
    }
    if(count > 0){
        if(item2str != 0) ss << item2str(data[count-1]);
        else  ss << data[count-1];
    }
    ss << "]";
    return ss.str();
}


//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////
template<class T>
void XArrayList<T>::checkIndex(int index){
    if((index < 0) || (index >= count))
        throw std::out_of_range("index is out of range");

}
template<class T>
void XArrayList<T>::ensureCapacity(int index){
    if((index < 0) || (index > count) ) //illegal
        throw std::out_of_range("the input index is out of range!");

    if(index >= capacity){
        //re-allocate 
        int old_capacity = capacity;
        capacity = old_capacity + (old_capacity >> 2);
        try{
            T* new_data = new T[capacity];
            memcpy(new_data, data, capacity*sizeof(T));
            delete []data;
            data = new_data;
        }
        catch(std::bad_alloc e){
            e.what();
        }
    }
}


#endif /* XARRAYLIST_H */

