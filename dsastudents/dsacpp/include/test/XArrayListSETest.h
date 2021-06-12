/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayListSETest.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 16:41
 */

#ifndef XARRAYLISTSETEST_H
#define XARRAYLISTSETEST_H

#include "doctest.h"
#include "sorting/XArrayListSE.h"
#include "util/Point.h"
#include "util/ArrayLib.h"

/*
#include "sorting/StraightInsertionSort.h"
#include "sorting/ShellSort.h"
#include "sorting/StraightSelectionSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/HeapSort.h"
*/

#include "sorting/QuickSort.h"

TEST_CASE( "XArrayListSE<int>[1]: adding items, then sorting" ) {
    int item[]      = {98, 65, 22, 11, 34, 28, 19, 8};
    int asc_exp[]   = {8, 11, 19, 22, 28, 34, 65, 98};
    int des_exp[]   = {98, 65, 34, 28, 22, 19, 11, 8};
    XArrayListSE<int> list;
    REQUIRE( list.size() == 0 );
    int size = 8;
    
    SUBCASE("Sorting Ascendingly"){
        for(int idx = 0; idx < size; idx++) list.add(item[idx]);
        //cout << left << setw(12) << "Original: " << list.toString() << endl;

        list.sort();
        //cout << left << setw(12) << "Ascending: "  << list.toString() << endl;
        //check
        XArrayListSE<int>::Iterator it;
        int idx = 0;
        for(it = list.begin(); it != list.end(); it++)
            REQUIRE(*it == asc_exp[idx++]);
        
    }
    SUBCASE("Sorting Descendingly"){
        for(int idx = 0; idx < size; idx++) list.add(item[idx]);
        //cout << left << setw(12) << "Original: " << list.toString() << endl;

        list.sort(&SortSimpleOrder<int>::compare4Desending);
        //cout << left << setw(12) << "Descending: "  << list.toString() << endl;
        //check
        XArrayListSE<int>::Iterator it;
        int idx = 0;
        for(it = list.begin(); it != list.end(); it++)
            REQUIRE(*it == des_exp[idx++]);
        
    }
}

bool isOrdered(XArrayListSE<int>& list, bool ascending=true){
    bool ordered = true;
    XArrayListSE<int>::Iterator it = list.begin();
    int prev = *it;
    it++;
    for(; it != list.end(); it++){
        int cur = *it;
        if(ascending){
            //is ascending?
            if(cur < prev){
                ordered = false;
                break;
            }
            else prev = cur;
        }
        else{
            //is descending?
            if(cur > prev){
                ordered = false;
                break;
            }
            else prev = cur;
        }
    }
    return ordered;
}

TEST_CASE( "XArrayListSE<int>[2]: randomly adding, then sort ascending" ) {
    XArrayListSE<int> list;
    for(int size = 1; size < 100; size++){
        int* array = genIntArray(size, -10, 10, true, 0);
        
        list.clear();
        REQUIRE(list.empty() == true);
        for(int idx=0; idx < size; idx++) list.add(array[idx]);
        REQUIRE(list.size() == size);
        
        list.sort(&SortSimpleOrder<int>::compare4Ascending);
        REQUIRE(isOrdered(list, true) == true);
        
        delete []array;
    }
}

TEST_CASE( "XArrayListSE<int>[2]: randomly adding, then sort descending" ) {
    XArrayListSE<int> list;
    for(int size = 1; size < 100; size++){
        int* array = genIntArray(size, -10, 10, true, 0);
        
        list.clear();
        REQUIRE(list.empty() == true);
        for(int idx=0; idx < size; idx++) list.add(array[idx]);
        REQUIRE(list.size() == size);
        
        list.sort(&SortSimpleOrder<int>::compare4Desending);
        REQUIRE(isOrdered(list, false) == true);
        
        delete []array;
    }
}

//Uncomment the following WHENEVER completing all the sorting algorithms used in the test below
/*
TEST_CASE( "XArrayListSE<int>: sorting with different algorithms" ) {
    int shell_segments[] = {1, 3, 7};
    ISort<int>* pAlgorithm[] ={
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()
    };
    
    SUBCASE("Random data"){
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int count = 1000;
            int* values = genIntArray(count, 0, 999999);

            XArrayListSE<int> list(0, 0, pAlgorithm[algIdx]);
            for(int idx=0; idx < count; idx++) list.add(values[idx]);
            list.sort(&SortSimpleOrder<int>::compare4Ascending);
            //Then check values: descending
            REQUIRE(isOrdered(list, true) == true);
            
            delete []values;
        }
        
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int count = 1000;
            int* values = genIntArray(count, 0, 999999);

            XArrayListSE<int> list(0, 0, pAlgorithm[algIdx]);
            for(int idx=0; idx < count; idx++) list.add(values[idx]);
            list.sort(&SortSimpleOrder<int>::compare4Desending);
            //Then check values: descending
            REQUIRE(isOrdered(list, false) == true);
            
            delete []values;
        }
    }
    for(int algIdx = 0; algIdx < 6; algIdx++) delete pAlgorithm[algIdx];
}

*/

#endif /* XARRAYLISTSETEST_H */

