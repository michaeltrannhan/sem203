/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 21:00
 */

#ifndef SLINKEDLISTSE_H
#define SLINKEDLISTSE_H

#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class SLinkedListSE: public SLinkedList<T>{
public:
    
    SLinkedListSE(
            void (*removeData)(SLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            SLinkedList<T>(removeData, itemEQ){
        
    };
    void sort(int (*comparator)(T&,T&)=0){
        if(this->count > 0){
            typename SLinkedList<T>::Node* first = this->head->next; //first user's data
            this->tail->next->next = 0; //to tail => to 0
            mergeSort(first, comparator);
            
            //find the last user's data
            typename SLinkedList<T>::Node* last = first;
            while(last->next != 0) last = last->next;
            
            //attach to head&tail of the list
            last->next = this->tail;
            this->tail->next = last;
            this->head->next = first;
        }
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
    void mergeSort(typename SLinkedList<T>::Node*& head, int (*comparator)(T&,T&)=0){
        if((head != 0) && (head->next != 0)){
            typename SLinkedList<T>::Node* second;
            devide(head, second);
            mergeSort(head, comparator);
            mergeSort(second, comparator);
            merge(head, second, comparator);
        }
    };
    void devide(typename SLinkedList<T>::Node*& first, typename SLinkedList<T>::Node*& second){
        //YOUR CODE HERE
    }
    void merge(typename SLinkedList<T>::Node*& first, typename SLinkedList<T>::Node*& second, int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
    }
};

#endif /* SLINKEDLISTSE_H */

