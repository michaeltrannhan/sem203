/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IntArray.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 20:21
 */

#ifndef INTARRAY_H
#define INTARRAY_H
#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

int* genIntArray(int size, int minValue=0, int maxValue=100, 
               bool manualSeed=false, int seedValue=0){

    int* head = new int[size];

    std::default_random_engine* engine;
    if(manualSeed)
        engine = new std::default_random_engine(static_cast<long unsigned int>(seedValue));
    else
        engine = new std::default_random_engine(static_cast<long unsigned int>(time(0)));
    uniform_int_distribution<int> dist(minValue, maxValue);

    //
    for(int idx=0; idx < size; idx++) head[idx] = dist(*engine);

    delete engine;
    return head;
}

template<class T>
bool isOrdered(T* array, int size, bool ascending ){
    bool ordered = true;
    for(int idx=0; idx < size-1; idx++){
        //check for ascending
        if(ascending){
            if(array[idx] > array[idx+1]){
                ordered = false;
                break;
            }
        }
        else{
            //check for descending
            if(array[idx] < array[idx+1]){
                ordered = false;
                break;
            }
        }
    }
    return ordered;
}


template<class T>
void println(T* array, int size){
    cout << "[\n";
    for(int idx=0; idx < size; idx++){
        cout << array[idx] << endl;
    }
    cout << "]\n" << endl;
}

template<class T>
void print(T* array, int size){
    cout << "[";
    for(int idx=0; idx < size-1; idx++){
        cout << array[idx] << ", ";
    }
    if(size > 0) cout << array[size-1] << "]\n";
    else cout << "]\n" << endl;
}

#endif /* INTARRAY_H */

