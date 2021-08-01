/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XHashMapTestASSIGN.h
 * Author: ltsach
 *
 * Created on July 9, 2021, 8:30 PM
 */

#ifndef XHASHMAPTESTASSIGN_H
#define XHASHMAPTESTASSIGN_H
#include "testassignments/commons.h"


int hash_code(int& key, int size){
    return abs(key) % size;
}
//duplicated keys: 2*size
int* create_keys(int size){
    int* ptr = permutation(size, true, 2021);
    int* keys = new int[size*2];
    for(int idx=0; idx< size; idx++){
        keys[idx] = ptr[idx];
        keys[idx + size] = ptr[idx];
    }
    delete []ptr;
    
    return keys;
}

TEST_CASE("XHashMap<int>: put => empty + size"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 5;
    int sizes[] = {0, 1, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        if(size == 0){
            REQUIRE(map.empty() == true);
            REQUIRE(map.size() == 0);
            continue;
        }
        int* keys = create_keys(size);
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = keys[kidx];
            int value = key*( 1 + kidx/size);
            map.put(key, value);
        }
        REQUIRE(map.size() == size);
        
        //
        delete []keys;
    }
}

TEST_CASE("XHashMap<int>: put same keys => update value"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 5;
    int sizes[] = {1, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        int* keys = create_keys(size);
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = keys[kidx];
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        //check values
        for(int kidx=0; kidx < size; kidx++){
            int key = keys[kidx];
            int exp_value = 2*key;
            REQUIRE(map.get(key) == exp_value);
        }
        
        //
        delete []keys;
    }
}

TEST_CASE("XHashMap<int>: remove => not found"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 4;
    int sizes[] = {50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        
        //remove a half number of keys
        int nremoved = size/2;
        for(int key=0; key < nremoved; key++){
            int value = map.remove(key);
            REQUIRE(value == 2*key);
            try{
                map.get(key);
            }
            catch(KeyNotFound e){
                REQUIRE(1==1); //reach here => pass
            }
        }
        //test found for remaining keys
        for(int key=nremoved; key < size; key++){
            try{
                REQUIRE(map.get(key) == 2*key);
            }
            catch(KeyNotFound& e){
                REQUIRE(1 !=1 ); //reach here => fail
            }
        }
    }
}


TEST_CASE("XHashMap<int>: containsKey, containsValue"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 4;
    int sizes[] = {50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        for(int key=0; key < size; key++){
            REQUIRE(map.containsKey(key) == true);
            REQUIRE(map.containsValue(2*key) == true);
        }
        for(int key=0; key < size; key++){
            REQUIRE(map.containsKey(key + 10*size) == false);
            REQUIRE(map.containsValue(2*(key + 10*size)) == false);
        }
    }
}

TEST_CASE("XHashMap<int>: remove => containsKey"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 4;
    int sizes[] = {50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        
        //remove a half number of keys
        int nremoved = size/2;
        for(int key=0; key < nremoved; key++){
            map.remove(key);
            REQUIRE(map.containsKey(key) == false);
        }
        //test found for remaining keys
        for(int key=nremoved; key < size; key++){
            REQUIRE(map.containsKey(key) == true);
        }
    }
}

TEST_CASE("XHashMap<int>: remove => containsValue"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 4;
    int sizes[] = {50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        
        //remove a half number of keys
        int nremoved = size/2;
        for(int key=0; key < nremoved; key++){
            map.remove(key);
            REQUIRE(map.containsValue(2*key) == false);
        }
        //test found for remaining keys
        for(int key=nremoved; key < size; key++){
            REQUIRE(map.containsValue(2*key) == true);
        }
    }
}


TEST_CASE("XHashMap<int>: remove(key, value) => containsKey, containsValue"){
    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 5;
    int sizes[] = {10, 50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        //map.println();
        
        //remove a half number of keys
        int nremoved = size/2;
        for(int key=0; key < nremoved; key++){
            if(key == 0){
                map.remove(key, key);
                REQUIRE(map.containsKey(key) == false);
                REQUIRE(map.containsValue(2*key) == false);
            }
            else{
                map.remove(key, key);
                REQUIRE(map.containsKey(key) == true);
                REQUIRE(map.containsValue(2*key) == true);
                map.remove(key, 2*key);
                REQUIRE(map.containsKey(key) == false);
                REQUIRE(map.containsValue(2*key) == false);
            }
        }
        //test found for remaining keys
        for(int key=nremoved; key < size; key++){
            REQUIRE(map.containsKey(key) == true);
            REQUIRE(map.containsValue(2*key) == true);
        }
    }
}

TEST_CASE("XHashMap<int>: using pairs"){
    XHashMap<int, int> map(&hash_code);
    Pair<int, int> pairs[] = {
        Pair<int, int>(10, 20),
        Pair<int, int>(20, 40),
        Pair<int, int>(40, 80),
        Pair<int, int>(50, 100),
        Pair<int, int>(60, 120),
        Pair<int, int>(70, 140)
    };
    for(Pair<int, int> pair: pairs) map.put(pair.key, pair.value);
    REQUIRE(map.size() == 6);
}

TEST_CASE("XHashMap<int>: Polymorphism"){
    IMap<int, int>* map = new XHashMap<int, int>(&hash_code);
    Pair<int, int> pairs[] = {
        Pair<int, int>(10, 20),
        Pair<int, int>(20, 40),
        Pair<int, int>(40, 80),
        Pair<int, int>(50, 100),
        Pair<int, int>(60, 120),
        Pair<int, int>(70, 140)
    };
    for(Pair<int, int> pair: pairs) map->put(pair.key, pair.value);
    REQUIRE(map->size() == 6);
}

TEST_CASE("XHashMap<int>: clear => actions"){
    XHashMap<int, int> map(&hash_code);
    Pair<int, int> pairs[] = {
        Pair<int, int>(10, 20),
        Pair<int, int>(20, 40),
        Pair<int, int>(40, 80),
        Pair<int, int>(50, 100),
        Pair<int, int>(60, 120),
        Pair<int, int>(70, 140)
    };
    for(Pair<int, int> pair: pairs) map.put(pair.key, pair.value);
    map.clear();
    REQUIRE(map.size() == 0);
    REQUIRE(map.empty() == true);
    
    for(Pair<int, int> pair: pairs) map.put(pair.key, pair.value);
    REQUIRE(map.size() == 6);
    
}

#endif /* XHASHMAPTESTASSIGN_H */

