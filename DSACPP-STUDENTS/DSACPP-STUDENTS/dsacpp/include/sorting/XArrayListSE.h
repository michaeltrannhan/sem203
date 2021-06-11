/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 16:01
 */

#ifndef XARRAYLISTSE_H
#define XARRAYLISTSE_H

#include "list/XArrayList.h"
#include "sorting/QuickSort.h"

template<class T>
class XArrayListSE: public XArrayList<T>{
public:
    XArrayListSE(
            void (*removeData)(XArrayList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0,
            ISort<T>* sortAlg=0): 
                XArrayList<T>(removeData, itemEQ){
                    
        useDefault = false;            
        if(sortAlg != 0) this->sortAlg = sortAlg;
        else{
            this->sortAlg = new QuickSort<T>(); //use QuickSort by default
            useDefault = true;
        } 
    };
    ~XArrayListSE(){
        if(useDefault) delete this->sortAlg; //DO NOT delete the external sort-algorithm
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        sortAlg->sort(this->data, this->count, comparator); 
    }
    
protected: 
    ISort<T>* sortAlg;
    bool useDefault;
};

#endif /* XARRAYLISTSE_H */

