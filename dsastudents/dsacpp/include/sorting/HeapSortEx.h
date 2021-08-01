/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapSortEx.h
 * Author: LTSACH
 *
 * Created on 14 September 2020, 18:10
 */

#ifndef HeapSortEX_H
#define HeapSortEX_H
#include "sorting/ISort.h"
#include "heap/Heap.h"

template <class T>
class HeapSortEx : private Heap<T>, public ISort<T>
{
public:
    HeapSortEx(int (*comparator)(T &, T &) = 0,
             void (*deleteUserData)(Heap<T> *) = 0) : Heap<T>(comparator, deleteUserData)
    {
    }
    void sort(T array[], int size, int (*comparator)(T &, T &) = 0, int stride = 1)
    {
        //YOUR CODE HERE
        if (comparator)
        {
            T *tempArr = new T[size];
            for(int i = 0; i < size;i++){
                tempArr[i] = array[i*stride];
            }
            Heap<T> heap(comparator);
            heap.heapify(array, size);
            for (int i = 0; i < size*stride; i+=stride)
            {
                T temp = heap.pop();
                array[i] = temp;
            }
        }
        else
        {
            T *tempArr = new T[size];
            for(int i = 0; i < size;i++){
                tempArr[i] = array[i*stride];
            }
            Heap<T> heap;
            heap.heapify(array, size);
            for (int i = 0; i < size*stride; i+=stride)
            {
                T temp = heap.pop();
                array[i] = temp;
            }
        }
    }
};

#endif /* HeapSortEx_H */
