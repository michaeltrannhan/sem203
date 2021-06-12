/*
 * Author: LTSACH
 */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
#include "util/ArrayLib.h"



struct Node{
    int value;
    Node(int value=0, Node* next=0){
        this->value = value;
        this->next = next;
    }
    Node* next;
};

/////////////////////////////////////////////////////////////////////////////
////////// ITERATIVE ALGORITHMS
/////////////////////////////////////////////////////////////////////////////

Node* createChain(int* array, int size=5){
    Node* pnext = 0;
    Node* pnode = 0;
    for(int idx=size-1; idx >=0 ; idx--){
        pnode = new Node(array[idx], pnext);
        pnext = pnode;
    }
    return pnode;
}

void printlnChain(Node* pnode){
    stringstream os;
    
    Node* cursor = pnode;
    while(cursor != NULL){
        os << cursor->value << ", ";
        cursor = cursor->next;
    }
    string str = os.str();
    
    if(pnode != NULL) str = str.substr(0, str.size() - 2);
    cout << "[" << str << "]" << endl;
}


void deleteChain(Node* pnode){
    Node* cursor = pnode;
    Node* pnext = 0;
    while(cursor != NULL){
        pnext = cursor->next;
        delete cursor;
        cursor = pnext;
    }
}

/////////////////////////////////////////////////////////////////////////////
////////// RECURSIVE ALGORITHMS
/////////////////////////////////////////////////////////////////////////////
Node* createChain_Recursion(Node* sub_head, int* array, int size=5){
    if(size == 0) return sub_head;
    
    Node* new_head = new Node(array[size-1], sub_head);
    return createChain_Recursion(new_head, array, size-1);
}

Node* createChain_Recursion(int* array, int size=5){
    Node* head = createChain_Recursion(0, array, size);
    return head;
}


void printlnChain_Recursion_Step(stringstream& os, Node* pnode){
    if(pnode == NULL) return;
    
    os << pnode->value << ", ";
    printlnChain_Recursion_Step(os, pnode->next);
}

void printlnChain_Recursion(Node* pnode){
    stringstream os;
    printlnChain_Recursion_Step(os, pnode);
    string str = os.str();
    
    if(pnode != NULL) str = str.substr(0, str.size() - 2);
    cout << "[" << str << "]" << endl;
}

void deleteChain_Recursion(Node* pnode){
    if(pnode == NULL) return;
    
    Node* pnext = pnode->next;
    delete pnode;
    deleteChain_Recursion(pnext);
}


/////////////////////////////////////////////////////////////////////////////
////////// MAIN
/////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv){
    int size = 5;
    int array[] = {12, 5, 8, 9, 4};
    Node * phead = createChain_Recursion(array, size);
    printlnChain_Recursion(phead);
    deleteChain_Recursion(phead);
    return 0;
}