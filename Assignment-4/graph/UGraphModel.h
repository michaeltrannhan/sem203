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
    class UGraphAlgorithm;
    friend class UGraphAlgorithm;
    
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


//////////////////////////////////////////////////////////////////////
//////////////////// Algorithms with UGraphModel  ////////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
class UGraphAlgorithm{
private:
public:
    UGraphAlgorithm(){
    }
    
    UGraphModel<T> minSpanningTree(UGraphModel<T>* pGraph){
        //(1) Obtain the list of vertices being processed
        //YOUR CODE HERE
        
        //(2) Process each vertex in vertexList
        //YOUR CODE HERE
    }
    
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
    
    class Edge{
    private:
        T from;
        T to;
        float weight;
        
        //friend class UGraphModel;
        friend class UGraphAlgorithm;
        
    public:
        Edge(T from, T to, float weight){
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
        
        static int edgeComparator(Edge*& edge1, Edge*& edge2){
            float diff = edge1->weight - edge2->weight;
            if(diff < 0) return -1;
            else if(diff > 0) return +1;
            else return 0;
        }
    };
    
};

#endif /* UGRAPHMODEL_H */

