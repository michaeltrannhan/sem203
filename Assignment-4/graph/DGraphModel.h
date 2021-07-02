/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/XHashMap.h"
#include "stacknqueue/PriorityQueue.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
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
//////////////////// Algorithms with DGraphModel  ////////////////////
//////////////////////////////////////////////////////////////////////
template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    
public:
    TopoSorter(DGraphModel<T>* graph){
        this->graph = graph;
    }   
    DLinkedList<T> sort(int mode=0){
        if(mode == DFS) return dfsSort();
        else return bfsSort();
    }
    DLinkedList<T> bfsSort(){
        //YOUR CODE HERE
    }
    DLinkedList<T> dfsSort(){
        //YOUR CODE HERE
    }
    
    
protected:
    XHashMap<T, int> vertex2inDegree(){
        XHashMap<T, int> map(&XHashMap<T, int>::simpleHash);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            map.put(vertex, inDegree);
            
            vertexIt++;
        }
        return map;
    }
    XHashMap<T, int> vertex2outDegree(){
        XHashMap<T, int> map(&XHashMap<T, int>::simpleHash);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int outDegree = this->graph->outDegree(vertex);
            map.put(vertex, outDegree);
            
            vertexIt++;
        }
        return map;
    }
    
    DLinkedList<T> listOfZeroInDegrees(){
        DLinkedList<T> list;
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            if(inDegree == 0) list.add(vertex);
            
            vertexIt++;
        }
        return list;
    }
}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


template<class T>
class DGraphAlgorithm{
public:
    class Node;
    DGraphAlgorithm(){}
    static bool vertexEQ(T& lhs, T& rhs){
        return lhs==rhs;
    }
    static bool nodeEQ(Node*& lhs, Node*& rhs){
        return vertexEQ(lhs->vertex, rhs->vertex);
    }
    static string item2str(T& item){
        stringstream os;
        os << item;
        return os.str();
    }
    DLinkedList<Path<T>*> dijkstra(DGraphModel<T>* pGraph, T start){
        DLinkedList<Node*> explored(0, DGraphAlgorithm<T>::nodeEQ);
        PriorityQueue<Node*> frontier(&Node::compare);
        frontier.push(new Node(0, start, 0, &DGraphAlgorithm<T>::vertexEQ));
        while(!frontier.empty()){
            Node *node = frontier.pop();
            explored.add(node);
            DLinkedList<T> children = pGraph->getOutwardEdges(node->vertex);
            
            typename DLinkedList<T>::Iterator childrenIt = children.begin();
            //YOUR CODE HERE
        }
        return constructPath(explored);
    }
    
    DLinkedList<Path<T>*> constructPath(DLinkedList<Node*> explored){
        
        DLinkedList<Path<T>*> list;
        typename DLinkedList<Node*>::Iterator it = explored.begin();
       //YOUR CODE HERE
        return list;
    }
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class Node{
    private:
        Node* parent;
        T vertex;
        float pathCost;
        bool (*vertexEQ_PTR)(T&,T&);
        
        friend class DGraphAlgorithm;
        
    public:
        Node(   Node* parent, T vertex, float pathCost, 
                bool (*vertexEQ_PTR)(T&,T&)){
            this->parent = parent;
            this->vertex = vertex;
            this->pathCost = pathCost;
            this->vertexEQ_PTR = vertexEQ_PTR;
        }
        bool equals(Node& node){
            return this->vertexEQ_PTR(this->vertex, node.vertex);
        }
        string toString(){
            stringstream os;
            os << this->vertex;
            return os.str();
        }
        static int compare(Node*& lhs, Node*& rhs){
            float diff = lhs->pathCost - rhs->pathCost;
            if(diff < 0) return -1;
            else if(diff > 0) return +1;
            else return 0;
        }
        
    };
};

#endif /* DGRAPHMODEL_H */

