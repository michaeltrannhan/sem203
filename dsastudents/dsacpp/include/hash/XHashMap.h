/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XHapMap.h
 * Author: LTSACH
 *
 * Created on 22 August 2020, 21:57
 */

#ifndef XHASHMAP_H
#define XHASHMAP_H
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory.h>
using namespace std;

#include "hash/IMap.h"
/**
Add class Pair in order to compile the following code successfully
Questions: why do we need this update?

Compile successfully:
XHashMap<int, int> map(&hash_code);
Pair<int, int> pairs[] = {
    Pair<int, int>(10, 20),
    Pair<int, int>(20, 40),
    Pair<int, int>(40, 80),
    Pair<int, int>(50, 100),
    Pair<int, int>(60, 120),
    Pair<int, int>(70, 140)
};
for(Pair<int, int> pair: pairs) map.put(pair.key, pair.value);
*/
template<class A, class B>
class Pair; 

template<class K, class V>
class XHashMap: public IMap<K,V>{
public:
    class Entry; //forward declaration
    
protected:
    Entry** table;  //array of Entry*; initialized with nullptr
    int capacity;   //size of table
    int count;      //number of entries stored hash-map
    float loadFactor; //define max number of entries can be stored (< (loadFactor * capacity))
    
    int (*hashCode)(K&,int); //hasCode(K key, int tableSize): tableSize means capacity
    bool (*keyEqual)(K&,K&);  //keyEqual(K& lhs, K& rhs): test if lhs == rhs
    bool (*valueEqual)(V&,V&); //valueEqual(V& lhs, V& rhs): test if lhs == rhs
    void (*deleteKeys)(XHashMap<K,V>*); //deleteKeys(XHashMap<K,V>* pMap): delete all keys stored in pMap
    void (*deleteValues)(XHashMap<K,V>*); //deleteValues(XHashMap<K,V>* pMap): delete all values stored in pMap
    
public:
    XHashMap(
            int (*hashCode)(K&,int),
            float loadFactor=0.75f,
            bool (*valueEqual)(V&, V&)=0,
            void (*deleteValues)(XHashMap<K,V>*)=0,
            bool (*keyEqual)(K&, K&)=0,
            void (*deleteKeys)(XHashMap<K,V>*)=0);
    
    XHashMap(const XHashMap<K,V>& map); //copy constructor
    XHashMap<K,V>& operator=(const XHashMap<K,V>& map); //assignment operator
    
    ~XHashMap();
    
    //Inherit from IMap:BEGIN
    V put(K key, V value);
    V& get(K key);
    V remove(K key, void (*deleteKeyInMap)(K)=0);
    bool remove(K key, V value, void (*deleteKeyInMap)(K)=0, void (*deleteValueInMap)(V)=0);
    bool containsKey(K key);
    bool containsValue(V value);
    bool empty();
    int size();
    void clear();
    string toString(string (*key2str)(K&)=0, string (*value2str)(V&)=0 );
    DLinkedList<K> keys();
    DLinkedList<V> values();
    DLinkedList<int> clashes();
    //Inherit from IMap:END
    
    //Show map on screen: need to convert key to string (key2str) and value2str
    void println(string (*key2str)(K&)=0, string (*value2str)(V&)=0 ){
        cout << this->toString(key2str, value2str) << endl;
    }
    int getCapacity(){
        return capacity;
    }
    
    /*
     * sample functions:
     * a) simpleHash(K& key, int capacity): a simple hash function
     * b) freeKey(XHashMap<K,V> *pMap): a typical function for deleting keys stored in map
     * c) freeValue(XHashMap<K,V> *pMap): a typical function for deleting values stored in map
     */
    static int simpleHash(K& key, int capacity){
        return key%capacity;
    }
    static void freeKey(XHashMap<K,V> *pMap){
        for(int idx=0; idx < pMap->capacity; idx++){
            Entry* entry = pMap->table[idx];
            while(entry != 0){
                delete entry->key;
                entry = entry->next;
            }
        }
    }
    static void freeValue(XHashMap<K,V> *pMap){
        for(int idx=0; idx < pMap->capacity; idx++){
            Entry* entry = pMap->table[idx];
            while(entry != 0){
                delete entry->value;
                entry = entry->next;
            }
        }
    }
 

protected:
    void ensureLoadFactor(int minCapacity);
    //should add method to trim table shorter when removing key (and value)
    void rehash(int newCapacity);
    void removeInternalData();
    void copyMapFrom(const XHashMap<K,V>& map);
    void moveEntries(Entry** oldTable, int oldCapacity, Entry** newTable, int newCapacity);
    
    bool keyEQ(K& lhs, K& rhs){
        if(keyEqual != 0) return keyEqual(lhs, rhs);
        else return lhs==rhs;
    }
    bool valueEQ(V& lhs, V& rhs){
        if(valueEqual != 0) return valueEqual(lhs, rhs);
        else return lhs==rhs;
    }
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    
    //Entry: BEGIN
    class Entry{
    private:
        K key;
        V value;
        Entry* prev;
        Entry* next;
        friend class XHashMap<K,V>;
        
    public:
        Entry(){
            this->prev = 0;
            this->next = 0;
        }
        Entry(K key, V value, Entry* prev=0, Entry* next=0){
            this->key = key;
            this->value = value;
            this->prev = prev;
            this->next = next;
        }
    };
    
    //Entry: END
};


//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class K, class V>
XHashMap<K,V>::XHashMap(
                int (*hashCode)(K&,int),
                float loadFactor,
                bool (*valueEqual)(V& lhs, V& rhs),
                void (*deleteValues)(XHashMap<K,V>*),
                bool (*keyEqual)(K& lhs, K& rhs),
                void (*deleteKeys)(XHashMap<K,V>* pMap) ){
    this->capacity = 10;
    this->count = 0;
    this->table = new Entry*[capacity];
    //reset table to nullptr
    for(int idx =0; idx < capacity; idx++){
        this->table[idx] = 0;
    }
    
    this->hashCode = hashCode;
    this->loadFactor = loadFactor;
    
    this->valueEqual = valueEqual;
    this->deleteValues = deleteValues;
    
    this->keyEqual = keyEqual;
    this->deleteKeys = deleteKeys;
    
}

template<class K, class V>
XHashMap<K,V>::XHashMap(const XHashMap<K,V>& map){
    copyMapFrom(map);
}

template<class K, class V>
XHashMap<K,V>& XHashMap<K,V>::operator=(const XHashMap<K,V>& map){
    removeInternalData();
    copyMapFrom(map);
    return *this;
}

template<class K, class V>
XHashMap<K,V>::~XHashMap(){
    removeInternalData();
}

template<class K, class V>
V XHashMap<K,V>::put(K key, V value){
    //YOUR CODE HERE
    int idx = hashCode(key, this->capacity);
    Entry *entry = this->table[idx];
    while(entry != nullptr)
    {
        if(keyEQ(entry->key, key)){
            V oldValue = entry->value;
            entry->value = value;
            return oldValue;
        }
        entry = entry->next;
    }
    Entry *newEntry = new Entry(key, value, 0, table[idx]);
    if(table[idx] != 0) table[idx]->prev = newEntry;
    table[idx] = newEntry;
    count++;
    ensureLoadFactor(count);
    return value;
}

template<class K, class V>
void XHashMap<K,V>::moveEntries(Entry** oldTable, int oldCapacity, 
        Entry** newTable, int newCapacity){
    
    for(int old_index=0; old_index < oldCapacity; old_index++){
        Entry* oldEntry = oldTable[old_index];
        while(oldEntry != 0){
            int new_index = this->hashCode(oldEntry->key, newCapacity);
            
            Entry* newEntry = new Entry(oldEntry->key, oldEntry->value, 0, newTable[new_index]);
            if(newTable[new_index] != 0) newTable[new_index]->prev = newEntry;
            newTable[new_index] = newEntry;
            
            oldEntry = oldEntry->next;
        }//while
    }//for
}


// template<class K, class V>
// V& XHashMap<K,V>::get(K key){
//     //YOUR CODE HERE
//     int idx = hashCode(key, this->capacity);
//     Entry *entry = table[idx];
//     while(entry != 0){
//         if(keyEQ(entry->key, key)){
//             return entry->value;
//         }
//         entry = entry->next;
//     }
    
//     //IF key: not found
//     stringstream os;
//     os << "key (" << entry->key << ") is not found";
//     throw KeyNotFound(os.str());
// }

template<class K, class V>
V& XHashMap<K,V>::get(K key){
    //YOUR CODE HERE
    int idx = hashCode(key, this->capacity);
    Entry *entry = table[idx];
    while(entry != 0){
        if(keyEQ(entry->key, key)){
            return entry->value;
        }
        entry = entry->next;
    }
    //key: not found
    stringstream os;
    //OLD: os << "key (" << entry->key << ") is not found";
    os << "key (" << key << ") is not found";
    throw KeyNotFound(os.str());
}


template<class K, class V>
V XHashMap<K,V>::remove(K key,void (*deleteKeyInMap)(K)){
    //YOUR CODE HERE
    int idx = hashCode(key, this->capacity);
    Entry *entry = this->table[idx];
    while(entry!=0){
        if(keyEQ(entry->key, key)){
            if(entry->prev == 0){
                Entry *head = entry->next;
                if(head != 0) head->prev = 0;
                table[idx] = head;
                entry->next = 0;

                V value = entry->value;
                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                delete entry;
                return value;
            }
            else if(entry->next == 0){
                Entry *prev = entry->prev;
                prev->next = 0;
                entry->prev = 0;

                V value = entry->value;
                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                delete entry;
                return value;
            }
            else{
                entry->prev->next = entry->next;
                entry->next->prev = entry->prev;
                entry->prev = entry->next = 0;

                V value = entry->value;
                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                delete entry;
                return value;
            }
            count --;
            entry = entry->next;
        }
    }
    //IF key: not found
    stringstream os;
    os << "key (" << entry->key << ") is not found";
    throw KeyNotFound(os.str());
}

// template<class K, class V>
// bool XHashMap<K,V>::remove(K key, V value, void (*deleteKeyInMap)(K), void (*deleteValueInMap)(V)){
//     //YOUR CODE HERE
//     int idx = hashCode(key, this->capacity);
//     Entry *entry = table[idx];
//     while(entry!=0){
//         if(keyEQ(entry->key, key) && valueEQ(entry->value, value)){
//             if(entry->prev == 0){
//                 Entry *head = entry->next;
//                 if(head != 0) head->prev = 0;
//                 table[idx] = head;
//                 entry->next = 0;

//                 if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
//                 if(deleteValueInMap != 0) deleteValueInMap(entry->value);
//                 delete entry;
//                 return true;
//             }
//             else if(entry->next == 0){
//                 Entry *prev = entry->prev;
//                 prev->next = 0;
//                 entry->prev = 0;

//                 if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
//                 if(deleteValueInMap != 0) deleteValueInMap(entry->value);
//                 delete entry;
//                 return true;
//             }
//             else{
//                 entry->prev->next = entry->next;
//                 entry->next->prev = entry->prev;
//                 entry->prev = entry->next = 0;

//                 if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
//                 if(deleteValueInMap !=0) deleteValueInMap(entry->value);
//                 delete entry;
//                 return true;
//             }
//             count --;
//             entry = entry->next;
//         }
//     }
//     return false;
// }

template<class K, class V>
bool XHashMap<K,V>::remove(K key, V value, void (*deleteKeyInMap)(K), void (*deleteValueInMap)(V)){
    //YOUR CODE HERE
    int index = hashCode(key, capacity);
    Entry* entry = table[index];
    while(entry != 0){
        if(keyEQ(entry->key, key) && valueEQ(entry->value, value)){
            count -= 1;
            //remove head 
            if(entry->prev == 0){
                Entry* newHead = entry->next;
                if(newHead != 0) newHead->prev = 0;
                table[index] = newHead;
                entry->next = 0;

                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                if(deleteValueInMap != 0) deleteValueInMap(entry->value);
                delete entry;
                return true;
            }
            //remove tail
            else if(entry->next == 0){
                Entry* prev = entry->prev;
                prev->next = 0;
                entry->prev = 0;

                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                if(deleteValueInMap != 0) deleteValueInMap(entry->value);
                delete entry;
                return true;
            }
            // remove internal node(between head and tail)
            else {
                entry->prev->next = entry->next;
                entry->next->prev = entry->prev;
                entry->prev = 0;
                entry->next = 0;

                if(deleteKeyInMap != 0) deleteKeyInMap(entry->key);
                if(deleteValueInMap != 0) deleteValueInMap(entry->value);
                delete entry;
                return true; 
            }
        }
        entry = entry->next; 
    }
    return false;
}

template<class K, class V>
bool XHashMap<K,V>::containsKey(K key){
    //YOUR CODE HERE
    int idx = hashCode(key, this->capacity);
    Entry *entry = table[idx];
    while(entry != 0){
        if(keyEQ(entry->key, key))  return true;
        entry = entry->next;
    }
    return false;
}

template<class K, class V>
bool XHashMap<K,V>::containsValue(V value){
    //YOUR CODE HERE
    for(int i = 0 ; i < capacity ; i ++){
        Entry *entry = table[i];
        while(entry != 0){
            if(valueEQ(value, entry->value))    return true;
            entry = entry->next;
        }
    }
    return false;
}
template<class K, class V>
bool XHashMap<K,V>::empty(){
    //YOUR CODE HERE
    return this->count == 0;
}

template<class K, class V>
int XHashMap<K,V>::size(){
    //YOUR CODE HERE
    return this->count;
}

template<class K, class V>
void XHashMap<K,V>::clear(){
    removeInternalData();
    
    //YOUR CODE HERE
    this->capacity = 10;
    this->count = 0;
    this->table = new Entry*[this->capacity];

    for(int i = 0; i < capacity; i ++){
        this->table[i] = nullptr;
    }
}

template<class K, class V>
string XHashMap<K,V>::toString(string (*key2str)(K&), string (*value2str)(V&)){
    stringstream os;
    string mark(50, '=');
    os << mark << endl;
    os << setw(12) << left << "capacity: "  << capacity << endl;
    os << setw(12) << left << "size: " << count << endl;
    for(int idx=0; idx < capacity; idx++){
        Entry* entry = table[idx];
        os << setw(4) << left << idx << ": ";
        stringstream itemos;
        while(entry != 0){
            itemos << " (";
            
            if(key2str != 0) itemos << key2str(entry->key);
            else itemos << entry->key;
            itemos << ",";
            if(value2str != 0) itemos << value2str(entry->value);
            else itemos << entry->value;
            
            itemos << ");";
            
            //next entry:
            entry = entry->next;
        }
        string valuestr = itemos.str();
        if(valuestr.length() > 0) valuestr = valuestr.substr(0, valuestr.length()-1);
        os << valuestr  << endl;
    }
    os << mark << endl;
  
    return os.str();
}

template<class K, class V>
DLinkedList<K> XHashMap<K,V>::keys(){
    DLinkedList<K> list;
    //YOUR CODE HERE
    for(int i = 0 ; i < capacity ; i ++){
        Entry *entry = table[i];
        while(!entry){
            list.add(entry->key);
            entry = entry->next;
        }
    }
    return list;
}

template<class K, class V>
DLinkedList<V> XHashMap<K,V>::values(){
    DLinkedList<V> list;
    //YOUR CODE HERE
    for(int i = 0 ; i < capacity ; i ++){
        Entry *entry = table[i];
        while(!entry){
            list.add(entry->value);
            entry = entry->next;
        }
    }
    return list;
}

template<class K, class V>
DLinkedList<int> XHashMap<K,V>::clashes(){
    DLinkedList<int> list;
    for(int idx=0; idx < capacity; idx++){
        Entry* entry = table[idx];
        int count = 0;
        while(entry != 0){
            count += 1;
            entry = entry->next;
        }
        list.add(count);
    }
    return list;
}
//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////

template<class K, class V>
void XHashMap<K,V>::ensureLoadFactor(int current_size){
    int maxSize = (int)(loadFactor*capacity);
   
    //cout << "ensureLoadFactor: count = " << count << "; maxSize = " << maxSize << endl;
    if(current_size >= maxSize){
        //grow: oldCapacity >> 1 (= oldCapacity/2)
        int oldCapacity = capacity;
        //int newCapacity = oldCapacity + (oldCapacity >> 1);
        int newCapacity = 1.5*oldCapacity;
        rehash(newCapacity);
    }   
}

template<class K, class V>
void XHashMap<K,V>::rehash(int newCapacity){
    //cout << "REHASH-BEGIN: old-capacity<-" << capacity << "; lf<-" << ((float)count/capacity) << "; new-capacity<-" << newCapacity << endl; 
    //cout << "current count: " << count << endl;
    Entry** oldTable = this->table;
    int oldCapacity = capacity;
    
    //Create new table:
    this->table = new Entry*[newCapacity];
    this->capacity = newCapacity; //keep "count" not changed
    
    for(int idx =0; idx < newCapacity; idx++){
        this->table[idx] = 0; //reset table to nullptr
    }
    
    //Move entries to new table from old table
    moveEntries(oldTable, oldCapacity, this->table, newCapacity);
    
    //remove entry in oldTable
    for(int idx=0; idx < oldCapacity; idx++){
        Entry* entry =  oldTable[idx];
        while(entry != 0){
            Entry * next = entry->next;
            delete entry;
            entry = next;
        }
    }
    //Remove oldTable
    delete []oldTable;
}

template<class K, class V>
void XHashMap<K,V>::removeInternalData(){
    //Remove user's data
    if(deleteKeys != 0) deleteKeys(this);
    if(deleteValues != 0) deleteValues(this);
        
    //Remove all entries in the current map
    for(int idx=0; idx < this->capacity; idx++){
        Entry* entry = this->table[idx];
        while(entry != 0){
            Entry * next = entry->next;
            delete entry;
            entry = next;
        }
    }
    //Remove table
    delete []table;
}

template<class K, class V>
void XHashMap<K,V>::copyMapFrom(const XHashMap<K,V>& map){
    //
    this->capacity = map.capacity;
    this->count = 0;
    this->table = new Entry*[capacity];
    //reset table to nullptr
    for(int idx =0; idx < capacity; idx++){
        this->table[idx] = 0;
    }
    
    this->hashCode = hashCode;
    this->loadFactor = loadFactor;
    
    this->valueEqual = valueEqual;
    this->keyEqual = keyEqual;
    //SHOULD NOT COPY: deleteKeys, deleteValues => delete ONLY TIME in map if needed
    
    
    //copy entries
    for(int idx=0; idx < map.capacity; idx++){
        Entry* entry = map.table[idx];
        while(entry != 0){
            this->put(entry->key, entry->value);
            entry = entry->next;
        }
    }
}

template<class A, class B>
class Pair{
    public:
        A key;
        B value;
    Pair(){
        key = 0;
        value = 0;
    }
    Pair(A key, B value){
        this->key = key;
        this->value = value;
    }
};

#endif /* XHASHMAP_H */

