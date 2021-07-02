/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListTest.h
 * Author: LTSACH
 *
 * Created on 27 August 2020, 08:27
 */

#ifndef SLINKEDLISTTESTASSIGN_H
#define SLINKEDLISTTESTASSIGN_H

#include "commons.h"


//////////////////////////////////////////////////////////////////////
///////////////// SLinkedList + Primitive Data Type //////////////////
//////////////////////////////////////////////////////////////////////


TEST_CASE( "SLinkedList<int>: appending items = add(*)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(items[i]);
        
        //enforce list size
        REQUIRE( list.size() == size );
        REQUIRE( list.empty() == ((size == 0) ? true: false));
        
        //enforce item equality
        SLinkedList<int>::Iterator it;
        int i;
        for(it=list.begin(), i=0; it != list.end(); it++, i++){
            REQUIRE(*it == items[i]);
        }
        
        delete []items;
    }
    delete []sizes;
}
TEST_CASE( "SLinkedList<int>: add first = add(0, *)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(0, items[i]);
        
        //enforce list size
        REQUIRE( list.size() == size );
        REQUIRE( list.empty() == ((size == 0) ? true: false));
        
        //enforce item equality
        for(int idx=0; idx < size-1; idx++){
            REQUIRE(list.get(idx) == items[size-1-idx]);
        }
        
        delete []items;
    }
    delete []sizes;
}
TEST_CASE( "SLinkedList<int>: add last = add(size, *)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(list.size(), items[i]);
        
        //enforce list size
        REQUIRE( list.size() == size );
        REQUIRE( list.empty() == ((size == 0) ? true: false));
        
        //enforce item equality
        SLinkedList<int>::Iterator it;
        int i;
        for(it=list.begin(), i=0; it != list.end(); it++, i++){
            REQUIRE(*it == items[i]);
        }
        
        delete []items;
    }
    delete []sizes;
}
TEST_CASE( "SLinkedList<int>: add at k (random)= add(k, *)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++){
            int k = genInt(0, list.size());
            list.add(k, items[i]);
            
            //enforce list size
            REQUIRE( list.size() == (i + 1));
            REQUIRE( list.get(k) == items[i]);
        }

        delete []items;
    }
    delete []sizes;
}

//Removal tests
TEST_CASE( "SLinkedList<int>: remove the first item = removeAt(0)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(items[i]);
        
        //enforce removals
        for(int i=0; i < size; i++){
            int value = list.removeAt(0);
            REQUIRE(value == items[i]);
        }
        REQUIRE(list.empty() == true);
        
        delete []items;
    }
    delete []sizes;
}
TEST_CASE( "SLinkedList<int>: remove the last item = removeAt(size-1)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(items[i]);
        
        //enforce removals
        for(int i=size-1; i >= 0; i--){
            int value = list.removeAt(list.size() - 1);
            REQUIRE(value == items[i]);
        }
        REQUIRE(list.empty() == true);
        
        delete []items;
    }
    delete []sizes;
}
TEST_CASE( "SLinkedList<int>: remove at k (random) = removeAt(k)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        for(int i=0; i < size; i++) list.add(items[i]);
        
        //enforce removals
        for(int i=0; i < size; i++){
            int k = genInt(0, list.size()-1);
            int value = list.removeAt(k);
            list.add(k, value);
            REQUIRE(value == items[k]);
        }
        REQUIRE(list.size() == size);
        
        delete []items;
    }
    delete []sizes;
}

TEST_CASE( "SLinkedList<int>: removeItem = removeItem(item)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        
        //enforce removals: success
        for(int i=0; i < size; i++) list.add(items[i]);
        for(int i=0; i < size; i++){
            bool code = list.removeItem(items[i]);
            REQUIRE(code == true);
        }
        REQUIRE(list.size() == 0);
        
        //enforce removals: fail
        for(int i=0; i < size; i++) list.add(items[i]);
        
        int notfound[] = {-5000, -4000, -1000, 1000, 3000, 5000}; 
        for(int item: notfound){
            bool code = list.removeItem(item);
            REQUIRE(code == false);
        }
        REQUIRE(list.size() == size);
        
        
        delete []items;
    }
    delete []sizes;
}

//test get
TEST_CASE( "SLinkedList<int>: get item at  = get(k)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        
        //enforce getting
        for(int i=0; i < size; i++) list.add(items[i]);
        for(int i=0; i < size; i++){
            int item = list.get(i);
            REQUIRE(item == items[i]);
        }
        
        try{
            list.get(-1);
        }
        catch(exception& e){
            REQUIRE(-1 == -1);
        }
        try{
            list.get(size);
        }
        catch(exception& e){
            REQUIRE(size == size);
        }
        
        delete []items;
    }
    delete []sizes;
}

TEST_CASE( "SLinkedList<int>: indexOf(item)" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        int size = sizes[idx];
        //int* items = genIntArray(size, -500, 500, true, 2021);
        
        //enforce indexOf
        for(int i=0; i < size; i++) list.add(i);
        //Found
        for(int i=0; i < size; i++){
            int index = list.indexOf(i);
            REQUIRE(index == i);
        }
        int notfound[] = {-6000, -4000, -2000, size, size + 10, size + 20};
        for(int item: notfound){
            int index = list.indexOf(item);
            REQUIRE(index == -1);
        }
        
        //delete []items;
    }
    delete []sizes;
}

TEST_CASE( "SLinkedList<int>: contains" ) {
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        int size = sizes[idx];
        //int* items = genIntArray(size, -500, 500, true, 2021);
        
        //enforce indexOf
        for(int i=0; i < size; i++) list.add(i);
        //Found
        for(int i=0; i < size; i++){
            bool found = list.contains(i);
            REQUIRE(found == true);
        }
        int notfound[] = {-6000, -4000, -2000, 1000, 3000, 5000};
        for(int item: notfound){
            bool found = list.contains(item);
            REQUIRE(found == false);
        }
        
        //delete []items;
    }
    delete []sizes;
}

TEST_CASE("SLinkedList<int>: iterator -> remove"){
    SLinkedList<int> list;
    REQUIRE( list.size() == 0 );

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        REQUIRE( list.size() == 0 );
        
        //appending
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021); //permutation(size, true, 2021);
        for(int i=0; i < size; i++) list.add(items[i]);
        
        //enforcing list size
        REQUIRE( list.size() == size );
        REQUIRE( list.empty() == ((size == 0) ? true: false));
        
        //remove items
        for(int idx =0; idx < size; idx++){
            int item = items[idx];
            
            //remove it
            SLinkedList<int>::Iterator it = list.begin();
            while(it != list.end()){
                if(*it == item){
                    it.remove();
                    REQUIRE(list.size() == size - 1 -idx);
                    it++;
                    break; //ONLY REMOVE one item (==*it) even many duplicated
                }
                it++;
            }
        }
        
        delete []items;
    }
    delete []sizes;
}

#endif /* SLINKEDLISTTESTASSIGN_H */

