/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exList.h
 * Author: LTSACH
 *
 * Created on 1 September 2020, 18:14
 */

#ifndef EXLIST_H
#define EXLIST_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "list/XArrayList.h"

void listSimpleDemo(){
    int item[] = {19, 34, 22, 4, 8, 32, 78, 89};
                // 0   1   2  3  4  5    6   7  8
    //declare a variable that is an instance of XArrayList of integer
    XArrayList<int> list;
    for(int i=0; i < 8; i++){
        list.add(item[i]); //your processing
    }
    
    //print out the list
    cout << list.toString() << endl;
    
    //(1) get each item in list, then cout
    //(cout << list.get(item[too bad]) ????????
    for(int i=0; i<list.size(); i++){
        cout << list.get(i) << ", ";
    }
    cout << endl;
    
    //(2) get each item in list, then cout: Iterator?
    XArrayList<int>::Iterator it;
    
    //at each of iteration, how to get the current item on list
    for(it = list.begin(); it != list.end(); it++) cout << *it << ", "; //your processing
  
    cout << endl;
    
    
    //(3) get each item in list, then cout: Iterator?
    it = list.begin();
    while(it != list.end()){
        cout << *it << ", ";
        
        //
        it++;
    }
    cout << endl;
    
    
    
}

#endif /* EXLIST_H */

