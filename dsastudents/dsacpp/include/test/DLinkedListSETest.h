/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSETest.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 15:06
 */

#ifndef DLINKEDLISTSETEST_H
#define DLINKEDLISTSETEST_H
#include "doctest.h"
#include "sorting/DLinkedListSE.h"
#include "util/Point.h"
#include "util/ArrayLib.h"

TEST_CASE( "DLinkedListSE<int>[1]: adding items, then sorting" ) {
    int item[]      = {98, 65, 22, 11, 34, 28, 19, 8};
    int asc_exp[]   = {8, 11, 19, 22, 28, 34, 65, 98};
    int des_exp[]   = {98, 65, 34, 28, 22, 19, 11, 8};
    DLinkedListSE<int> list;
    REQUIRE( list.size() == 0 );
    int size = 8;
    
    SUBCASE("Sorting Ascendingly"){
        for(int idx = 0; idx < size; idx++) list.add(item[idx]);
        //cout << left << setw(12) << "Original: " << list.toString() << endl;

        list.sort();
        //check
        DLinkedList<int>::Iterator it;
        int idx = 0;
        for(it = list.begin(); it != list.end(); it++)
            REQUIRE(*it == asc_exp[idx++]);
        //cout << left << setw(12) << "Ascending: "  << list.toString() << endl;
    }
    SUBCASE("Sorting Descendingly"){
        for(int idx = 0; idx < size; idx++) list.add(item[idx]);
        //cout << left << setw(12) << "Original: " << list.toString() << endl;

        list.sort(&SortSimpleOrder<int>::compare4Desending);
        //check
        DLinkedList<int>::Iterator it;
        int idx = 0;
        for(it = list.begin(); it != list.end(); it++)
            REQUIRE(*it == des_exp[idx++]);
        //cout << left << setw(12) << "Descending: "  << list.toString() << endl;
    }
}

TEST_CASE( "DLinkedListSE<int>[2]: adding items" ) {
    DLinkedListSE<int> list;
    REQUIRE( list.size() == 0 );
    int size = 10;
    
 
    SUBCASE("Adding with add(item)"){
        for(int idx=0; idx < size; idx++){
            list.add(idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == idx);
        }
    }
    
    SUBCASE("Adding with add(index:0, item)"){
        for(int idx=0; idx < size; idx++){
            list.add(0, idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == (size - 1 -idx) );
        }
    }
    SUBCASE("Adding with add(index:size(), item)"){
        for(int idx=0; idx < size; idx++){
            list.add(list.size(), idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == idx );
        }
    }
    SUBCASE("Adding with add(index:any, item)"){
        int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
        //                0   1   2   3   4   5   6    7
        int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
        int expvalues[]= {8,  15, 2,  4,  7, 10,  40,  6}; 
        for(int idx=0; idx < 8; idx++){
            list.add(index[idx], values[idx]);
        }
        REQUIRE( list.size() == 8 );
        
        for(int idx=0; idx < 8; idx++){
            REQUIRE(list.get(idx) == expvalues[idx]);
        }
    }
}

bool isOrdered(DLinkedListSE<int>& list, bool ascending=true){
    bool ordered = true;
    DLinkedListSE<int>::Iterator it = list.begin();
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

bool isOrderedBWD(DLinkedListSE<int>& list, bool ascending=true){
    bool ordered = true;
    DLinkedListSE<int>::BWDIterator it = list.bbegin();
    int next = *it;
    it--;
    for(; it != list.bend(); it--){
        int cur = *it;
        if(ascending){
            //is ascending?
            if(cur > next){
                ordered = false;
                break;
            }
            else next = cur;
        }
        else{
            //is descending?
            if(cur < next){
                ordered = false;
                break;
            }
            else next = cur;
        }
    }
    return ordered;
}

TEST_CASE( "DLinkedListSE<int>[3]: randomly adding, then sort ascending" ) {
    DLinkedListSE<int> list;
    for(int size = 1; size < 100; size++){
        int* array = genIntArray(size, -10, 10, true, 0);
        
        list.clear();
        REQUIRE(list.empty() == true);
        for(int idx=0; idx < size; idx++) list.add(array[idx]);
        REQUIRE(list.size() == size);
        
        list.sort(&SortSimpleOrder<int>::compare4Ascending);
        REQUIRE(isOrdered(list, true) == true);
        REQUIRE(isOrderedBWD(list, true) == true);
        
        delete []array;
    }
}

TEST_CASE( "DLinkedListSE<int>[4]: randomly adding, then sort descending" ) {
    DLinkedListSE<int> list;
    for(int size = 1; size < 100; size++){
        int* array = genIntArray(size, -10, 10, true, 0);
        
        list.clear();
        REQUIRE(list.empty() == true);
        for(int idx=0; idx < size; idx++) list.add(array[idx]);
        REQUIRE(list.size() == size);
        
        list.sort(&SortSimpleOrder<int>::compare4Desending);
        REQUIRE(isOrdered(list, false) == true);
        REQUIRE(isOrderedBWD(list, false) == true);
        
        delete []array;
    }
}



#endif /* DLINKEDLISTSETEST_H */

