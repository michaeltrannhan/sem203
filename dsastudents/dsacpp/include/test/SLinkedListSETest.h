/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListSETest.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 21:10
 */

#ifndef SLINKEDLISTSETEST_H
#define SLINKEDLISTSETEST_H

#include "doctest.h"
#include "sorting/SLinkedListSE.h"
#include "util/Point.h"

TEST_CASE( "SLinkedListSE<int>[1]: adding items, then sorting" ) {
    int item[]      = {98, 65, 22, 11, 34, 28, 19, 8};
    int asc_exp[]   = {8, 11, 19, 22, 28, 34, 65, 98};
    int des_exp[]   = {98, 65, 34, 28, 22, 19, 11, 8};
    SLinkedListSE<int> list;
    REQUIRE( list.size() == 0 );
    int size = 8;
    
    SUBCASE("Sorting Ascendingly"){
        for(int idx = 0; idx < size; idx++) list.add(item[idx]);
        //cout << left << setw(12) << "Original: " << list.toString() << endl;

        list.sort();
        //check
        SLinkedListSE<int>::Iterator it;
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
        SLinkedListSE<int>::Iterator it;
        int idx = 0;
        for(it = list.begin(); it != list.end(); it++)
            REQUIRE(*it == des_exp[idx++]);
        //cout << left << setw(12) << "Descending: "  << list.toString() << endl;
    }
}

bool isOrdered(SLinkedListSE<int>& list, bool ascending=true){
    bool ordered = true;
    SLinkedListSE<int>::Iterator it = list.begin();
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


TEST_CASE( "SLinkedListSE<int>[2]: randomly adding, then sort ascending" ) {
    SLinkedListSE<int> list;
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

TEST_CASE( "SLinkedListSE<int>[3]: randomly adding, then sort descending" ) {
    SLinkedListSE<int> list;
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


#endif /* SLINKEDLISTSETEST_H */

