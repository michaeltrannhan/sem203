/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightInsertionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 16:24
 */

#ifndef STRAIGHTINSERTIONSORT_H
#define STRAIGHTINSERTIONSORT_H
#include "sorting/ISort.h"

template <class T>
class StraightInsertionSort : public ISort<T>
{
public:
    void sort(T array[], int size, int (*comparator)(T &, T &))
    {
        //YOUR CODE HERE
        int walker;
        int current = 1;
        while(current < size){
            T temp = array[current];
            walker = current -1;
            while(walker >= 0 && comparator(array[walker], temp) > 0){
                array[walker + 1] = array[walker];
                walker = walker - 1;
            }
            array[walker+1] = temp;
            current = current +1;
        }
    }
};

#endif /* STRAIGHTINSERTIONSORT_H */
