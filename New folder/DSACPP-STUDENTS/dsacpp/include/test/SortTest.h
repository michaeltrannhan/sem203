/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortTest.h
 * Author: LTSACH
 *
 * Created on 27 August 2020, 13:03
 */

#ifndef SORTTEST_H
#define SORTTEST_H



#include "doctest.h"

#include "sorting/StraightInsertionSort.h"
#include "sorting/ShellSort.h"
#include "sorting/StraightSelectionSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/HeapSort.h"
#include "sorting/QuickSort.h"
#include "util/Point.h"
#include "util/ArrayLib.h"

TEST_CASE( "Sorting ascending" ) {
    int shell_segments[] = {1, 3, 7};
    ISort<int>* pAlgorithm[] ={
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()
    };
    SUBCASE("Sample data"){
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int values[] = {45, 97, 12,  2,  39,  3,  37, 87};

            pAlgorithm[algIdx]->sort(values, 8, &SortSimpleOrder<int>::compare4Ascending);

            //Then check values: ascending
            int exp[] =  {2,  3,  12,  37, 39,  45, 87, 97};
            for(int idx=0; idx < 8; idx++){
                REQUIRE(values[idx] == exp[idx]);
            }
        }
    }
    SUBCASE("Random data"){
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int count = 1000;
            int* values = genIntArray(count, 0, 999999);

            pAlgorithm[algIdx]->sort(values, count, &SortSimpleOrder<int>::compare4Ascending);

            //Then check values: ascending
            REQUIRE(isOrdered(values, count, true) == true);
            
            delete []values;
        }
    }
    //Delete sorters
    for(int algIdx = 0; algIdx < 5; algIdx++){
        delete pAlgorithm[algIdx];
    }
}

TEST_CASE( "Sorting ascending" ) {
    int shell_segments[] = {1, 3, 7};
    ISort<int>* pAlgorithm[] ={
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()
    };
    
    SUBCASE("Sample data"){
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int values[] = {45, 97, 12,  2,  39,  3,  37, 87};

            pAlgorithm[algIdx]->sort(values, 8, &SortSimpleOrder<int>::compare4Desending);

            //Then check values: descending 
            int exp[] =  {97,  87, 45, 39,  37,  12,  3,  2}; 
            for(int idx=0; idx < 8; idx++){
                REQUIRE(values[idx] == exp[idx]);
            }
        }
    }
    SUBCASE("Random data"){
        for(int algIdx = 0; algIdx < 6; algIdx++){
            int count = 1000;
            int* values = genIntArray(count, 0, 999999);

            pAlgorithm[algIdx]->sort(values, count, &SortSimpleOrder<int>::compare4Desending);

            //Then check values: descending
            REQUIRE(isOrdered(values, count, false) == true);
            
            delete []values;
        }
    }
    
    //Delete sorters
    for(int algIdx = 0; algIdx < 6; algIdx++){
        delete pAlgorithm[algIdx];
    }
} 

#endif /* SORTTEST_H */

