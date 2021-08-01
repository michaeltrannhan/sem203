/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BubbleSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:16
 */

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sorting/ISort.h"

template <class T>
class BubbleSort : public ISort<T>
{
public:
    void swap(T* elements, int aidx, int bidx){
        T temp = elements[aidx];
        elements[aidx] = elements[bidx];
        elements[bidx] = temp;
    }
    void sort(T array[], int size, int (*comparator)(T &, T &))
    {
        //YOUR CODE HERE
        bool swapped = false;
        int i, j;
        for (i = 0; i < size; i++)
        {
            swapped = false;
            for (j = 1; j < size ; j++){
                if(comparator(array[j-1], array[j])>0){
                   swap(array,j-1, j );
                   swapped = true;
                }
            }
            if(swapped==false) break;
        }
    }
};

#endif /* BUBBLESORT_H */
