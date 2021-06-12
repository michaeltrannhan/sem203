/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QuickSort.h
 * Author: LTSACH
 *
 * Created on 14 September 2020, 18:26
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "sorting/ISort.h"

template<class T>
class QuickSort: public ISort<T>{
private:
    int (*pivotSelection)(T*, int)=0;
public:
    QuickSort(int (*pivotSelection)(T*, int)=0){
        this->pivotSelection = pivotSelection;
    }
    void sort(T array[], int size, int (*comparator)(T&,T&) =0){
        quicksort(array, size, comparator, this->pivotSelection);
    }
    
private:
    void swap(T* elements, int aidx, int bidx){
        T temp = elements[aidx];
        elements[aidx] = elements[bidx];
        elements[bidx] = temp;
    };
    void quicksort(T* elements, int size, int (*comparator)(T&,T&)=0, int (*pivotSelection)(T*, int)=0){
        if(size >= 2){
            //pickup a pivot
            int pivot;
            if(pivotSelection != 0) pivot = pivotSelection(elements, size);
            else pivot = pickupPivot(elements, size);
            
            //swap the pivot with the first
            swap(elements, 0, pivot);
            
            //
            int too_big_index = 1;
            int too_small_index = size - 1;
            while(too_small_index > too_big_index){
                while(  (too_big_index < size) && 
                        (compare(elements[too_big_index], elements[0], comparator) <= 0) ) 
                    too_big_index += 1;
                while(  (too_small_index > 0) && 
                        (compare(elements[too_small_index], elements[0], comparator) > 0) ) 
                    too_small_index -= 1;
                if(too_big_index < too_small_index) swap(elements, too_small_index, too_big_index);
            }
            if(compare(elements[too_small_index], elements[0], comparator) < 0)
                swap(elements, too_small_index, 0);
            
            //call recursively
            /*Now:
             * left unsorted-list: [0, too_small_index)
             * element at right position: too_small_index
             * right unosorted-list: [too_small_index + 1, size)
             */
            int left_start = 0;
            int left_size = too_small_index;
            int right_start = too_small_index + 1;
            int right_size = (size - 1) - right_start + 1;
            quicksort(&elements[left_start], left_size, comparator, pivotSelection);
            quicksort(&elements[right_start], right_size, comparator, pivotSelection);
        }
    }
    
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    };
    
    /*pickupPivot:
     *  use "median of threes
     */
    static int pickupPivot(T* elements, int size){
        if(size <= 0) throw std::out_of_range("Invalid size");
        if((size == 1) || (size == 2)) return 0;
        else{
            int first = 0, mid = int(size/2), last = (size - 1);
            if ((first > mid) != (first > last)) 
                return first;
            else if ((mid > first) != (mid > last)) 
                return mid;
            else
                return last;
        }
    };
};


#endif /* QUICKSORT_H */

