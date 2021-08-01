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
#include "graph/IGraph.h"
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
        typename AbstractGraph<T>::VertexNode *nodeF = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *nodeT = this->getVertexNode(to);
        if(nodeF == 0) throw VertexNotFoundException(this->vertex2Str(*nodeF));
        if(nodeT == 0) throw VertexNotFoundException(this->vertex2Str(*nodeT));

        if(nodeF->equals(nodeT)){
            nodeF->connect(nodeT, weight);
        }
        else{
            nodeF->connect(nodeT, weight);
            nodeT->connect(nodeF, weight);
        }
    }
    void disconnect(T from, T to){
        //YOUR CODE HERE
        typename AbstractGraph<T>::VertexNode *nodeF = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *nodeT = this->getVertexNode(to);
        if(nodeF == 0) throw VertexNotFoundException(this->vertex2Str(*nodeF));
        if(nodeT == 0) throw VertexNotFoundException(this->vertex2Str(*nodeT));

        typename AbstractGraph<T>::Edge *edge =nodeF->getEdge(nodeT);
        if(edge == 0) throw EdgeNotFoundException(this->edge2Str(*edge));
        if(nodeF->equals(nodeT)){
            nodeF->removeTo(nodeT);
        }
        else{
            nodeF->removeTo(nodeT);
            nodeT->removeTo(nodeF);
        }
    }
    void remove(T vertex){
        //YOUR CODE HERE
        typename AbstractGraph<T>::VertexNode *nodeA = this->getVertexNode(vertex);
        if(nodeA == 0) throw VertexNotFoundException(this->vertex2Str(*nodeA));

        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator nodeIt = this->nodeList.begin();
        while(nodeIt != this->nodeList.end()){
            typename AbstractGraph<T>::VertexNode *nodeB = *nodeIt;
            typename AbstractGraph<T>::Edge *egde = nodeB->getEdge(nodeA);
            if(egde != 0){
            nodeB->removeTo(nodeA);
            nodeA->removeTo(nodeB);
            }
            nodeIt++;
        }
        this->nodeList.removeItem(nodeA);
    }
    static UGraphModel<T> *create(T *vertices, int nvertices, Edge<T> *edges, int nedges, bool (*vertexEQ)(T &, T &), string (*vertex2str)(T &))
    {
        UGraphModel<T> *model = new UGraphModel<T>(vertexEQ, vertex2str);
        for (int vidx = 0; vidx < nvertices; vidx++)
        {
            model->add(vertices[vidx]);
        }
        for (int eidx = 0; eidx < nedges; eidx++)
        {
            model->connect(edges[eidx].from, edges[eidx].to, edges[eidx].weight);
        }
        return model;
    }
};



#endif /* UGRAPHMODEL_H */

