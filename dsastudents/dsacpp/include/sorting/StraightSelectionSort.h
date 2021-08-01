/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightSelectionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:10
 */

#ifndef STRAIGHTSELECTIONSORT_H
#define STRAIGHTSELECTIONSORT_H

#include "sorting/ISort.h"


template<class T>
class StraightSelectionSort: public ISort<T>{
public:   
    void sort(T array[], int size, int (*comparator)(T&,T&)){
        //YOUR CODE HERE
        int current, smallest, walker;
        current = 0;
        while(current < size -1){
            smallest = current;
            walker = current + 1;
            while (walker < size){
                if(comparator(array[smallest], array[walker])>0){
                    smallest = walker;
                }
                walker++;
            }
            if(smallest != current){
                T temp = array[smallest];
                array[smallest] = array[current];
                array[current] = temp;
            }
            current += 1;
        }
    }
};



#endif /* STRAIGHTSELECTIONSORT_H */

