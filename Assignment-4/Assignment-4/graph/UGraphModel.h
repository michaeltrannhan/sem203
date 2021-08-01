/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
#include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class UGraphModel: public AbstractGraph<T>{
private:
public:
    //class UGraphAlgorithm;
    //friend class UGraphAlgorithm;
    
    UGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //YOUR CODE HERE
    }
    void disconnect(T from, T to){
        //YOUR CODE HERE
    }
    void remove(T vertex){
        //YOUR CODE HERE
    }
};



#endif /* UGRAPHMODEL_H */

