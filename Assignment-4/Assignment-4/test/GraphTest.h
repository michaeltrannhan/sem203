/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphTest.h
 * Author: LTSACH
 *
 * Created on 27 August 2020, 13:43
 */

#ifndef GRAPHTEST_H
#define GRAPHTEST_H
#include "doctest.h"
#include "graph/DGraphModel.h"
#include "graph/UGraphModel.h"


//////////////////////////////////////////////////////////////////////
////////////////////////  DGraphModel Test        ////////////////////
//////////////////////////////////////////////////////////////////////


bool charComparator(char& lhs, char& rhs){
    return lhs==rhs;
}
string vertex2str(char& v){
    stringstream os;
    os << v;
    return os.str();
}

TEST_CASE( "DGraphModel<char>:" ) {
    DGraphModel<char> model(&charComparator, &vertex2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    SUBCASE("1/Adding nodes => size/empty"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        REQUIRE(model.size() == 4);
        REQUIRE(model.empty() == false);
    }
    SUBCASE("2/Adding nodes => contains"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        for(int idx=0; idx < 4; idx++){
            REQUIRE(model.contains(vertices[idx]) == true);
        }
        REQUIRE(model.contains('E') == false);
        REQUIRE(model.contains('F') == false);
        
        model.clear();
        REQUIRE(model.size() == 0);
        REQUIRE(model.empty() == true);
        for(int idx=0; idx < 4; idx++){
            REQUIRE(model.contains(vertices[idx]) == false);
        }
    }
    SUBCASE("3/Adding nodes => remove/contains"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        for(int idx=0; idx < 4; idx++){
            model.remove(vertices[idx]);
            REQUIRE(model.contains(vertices[idx]) == false);
            model.add(vertices[idx]);
            REQUIRE(model.contains(vertices[idx]) == true);
        }
    }
    SUBCASE("4/Adding/Connecting nodes => in-degree/out-degree"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        model.connect('A', 'B');
        model.connect('B', 'D');
        model.connect('C', 'B');
        model.connect('C', 'D');
        int indegree[] =  {0, 2, 0, 2};
        int outdegree[] = {1, 1, 2, 0};
        for(int idx=0; idx < 4; idx++){
            REQUIRE(model.inDegree(vertices[idx]) == indegree[idx]);
            REQUIRE(model.outDegree(vertices[idx]) == outdegree[idx]);
        }
    }
    SUBCASE("5/Adding/Connecting nodes => outward/inward list"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        model.connect('A', 'B');
        model.connect('B', 'D');
        model.connect('C', 'B');
        model.connect('C', 'D');
        int outward_list[][4] ={
            {'B'}, //from A
            {'D'}, //from B
            {'B', 'D'}, //from C
            {} //from D
        };
        int outward_count[] = {1,1,2,0};
        
        int inward_list[][4] ={
            {}, //to A
            {'A', 'C'}, //to B
            {}, //to C
            {'B', 'C'} //to D
        };
        int inward_count[] = {0, 2, 0, 2};
        
        for(int idx=0; idx < 4; idx++){
            char vertex = vertices[idx];
            
            DLinkedList<char> inlist = model.getInwardEdges(vertex);
            REQUIRE(inlist.size() == inward_count[idx]);
            for(int c=0; c < inward_count[idx]; c++)
                REQUIRE(inlist.contains(inward_list[idx][c]) == true);
            
            DLinkedList<char> outlist = model.getOutwardEdges(vertex);
            REQUIRE(outlist.size() == outward_count[idx]);
            for(int c=0; c < outward_count[idx]; c++)
                REQUIRE(outlist.contains(outward_list[idx][c]) == true);
        }
    }
    SUBCASE("6/Adding/Connecting nodes => weight"){
        char vertices[] = {'A', 'B', 'C', 'D'};
        char from[]         = {'A',  'B', 'C',   'C'};
        char to[]           = {'B',  'D', 'B',   'D'};
        float weight[]      = {100,  200,  300,   400};

        for(int idx=0; idx < 4; idx++){
            model.add(vertices[idx]);
        }
        for(int idx=0; idx < 4; idx++){
            model.connect(from[idx], to[idx], weight[idx]);
        }
       
        //check
        for(int idx=0; idx < 4; idx++){
            char f = from[idx];
            char t = to[idx];
            float w = weight[idx];
            REQUIRE(model.weight(f,t) == w);
        }
    }
    SUBCASE("7/Adding/Connecting nodes/disconnect =>in/outward link"){
        char vertex[] = {'A', 'B', 'C', 'D'};
        int nv = 4;
        int ne = 4;
        
        char from[]         = {'A',  'B', 'C',   'C'};
        char to[]           = {'B',  'D', 'B',   'D'};
        float weight[]      = {100,  200,  300,   400};
        
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
        
        REQUIRE(model.size() == nv);
        REQUIRE(model.empty() == false);
        
        model.disconnect('A', 'B');
        model.disconnect('B', 'D');
        
        //expected
        int indegree[]      = { 0,  1,  0,  1};
        int outdegree[]     = { 0,  0,  2,  0}; 
        for(int v=0; v < nv; v++){
            REQUIRE(model.inDegree(vertex[v]) == indegree[v]);
            REQUIRE(model.outDegree(vertex[v]) == outdegree[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////////
////////////////////////  UGraphModel Test        ////////////////////
//////////////////////////////////////////////////////////////////////

bool charEQ(char& lhs, char& rhs){
    return lhs == rhs;
}
string char2str(char& item){
    stringstream os;
    os << item;
    return os.str();
}
TEST_CASE( "UGraphModel<char>" ) {
    UGraphModel<char> model(&charEQ, &char2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    int nv = 6;
    int ne = 9;
    char vertex[]       = {'A', 'B', 'C', 'D', 'E', 'F'};
    int indegree[]      = { 2,   3,   4,   4,   3,   2};
    int outdegree[]     = { 2,   3,   4,   4,   3,   2}; //UGraph: in=out-degree
    char from[]         = {'A',  'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E'};
    char to[]           = {'B',  'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F'};
    float weight[]      = { 6,    3,   2,   5,   3,   4,   2,   3,   5};
    char connect[][6]   {
        {'B', 'C'}, //for A
        {'A', 'C', 'D'}, //for B
        {'A', 'B', 'D', 'E'}, //for C
        {'B', 'C', 'E', 'F'}, //for D
        {'C', 'D', 'F'}, //for E
        {'D', 'E'} //for F
    };
    

    SUBCASE("1/Adding nodes => size/empty"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
        
        REQUIRE(model.size() == nv);
        REQUIRE(model.empty() == false);
    }
    SUBCASE("2/Adding nodes => contains"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int v=0; v < nv; v++){
            REQUIRE(model.contains(vertex[v]) == true);
        }
        REQUIRE(model.contains('S') == false);
        REQUIRE(model.contains('T') == false);
        
        model.clear();
        REQUIRE(model.size() == 0);
        REQUIRE(model.empty() == true);
        for(int v=0; v < nv; v++){
            REQUIRE(model.contains(vertex[v]) == false);
        }
    }
    SUBCASE("3/Adding nodes => remove/contains"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int v=0; v < nv; v++){
            model.remove(vertex[v]);
            REQUIRE(model.contains(vertex[v]) == false);
            model.add(vertex[v]);
            REQUIRE(model.contains(vertex[v]) == true);
        }
    }
    SUBCASE("4/Adding/Connecting nodes => in-degree/out-degree"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
        
        for(int v=0; v < nv; v++) {
            REQUIRE(model.inDegree(vertex[v]) == indegree[v]);
            REQUIRE(model.outDegree(vertex[v]) == outdegree[v]);
        }
    }
    SUBCASE("5/Adding/Connecting nodes => outward/inward list"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
        
        for(int v=0; v < nv; v++){
            char vn = vertex[v];
            
            DLinkedList<char> inlist = model.getInwardEdges(vn);
            REQUIRE(inlist.size() == indegree[v]); //=outdegree[v], also
            for(int c=0; c < indegree[v]; c++)
                REQUIRE(inlist.contains(connect[v][c]) == true);
            
            DLinkedList<char> outlist = model.getOutwardEdges(vn);
            REQUIRE(outlist.size() == outdegree[v]);
            for(int c=0; c < outdegree[v]; c++)
                REQUIRE(outlist.contains(connect[v][c]) == true);
        }
    }
    SUBCASE("6/Adding/Connecting nodes => weight"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
       
        //check
        for(int v=0; v < nv; v++) 
            REQUIRE(model.weight(from[v], to[v]) == weight[v]);
    }
    
    SUBCASE("7/Adding/Connecting nodes/disconnect =>in/outward link"){
        for(int v=0; v < nv; v++) model.add(vertex[v]);
        for(int e=0; e < ne; e++) model.connect(from[e], to[e], weight[e]);
        
        REQUIRE(model.size() == nv);
        REQUIRE(model.empty() == false);
        
        model.disconnect('A', 'B');
        model.disconnect('B', 'C');
        model.disconnect('C', 'D');
        model.disconnect('E', 'F');
        
        //expected
        int indegree[]      = { 1,   1,   2,   3,   2,   1};
        int outdegree[]     = { 1,   1,   2,   3,   2,   1}; //UGraph: in=out-degree
        for(int v=0; v < nv; v++){
            REQUIRE(model.inDegree(vertex[v]) == indegree[v]);
            REQUIRE(model.outDegree(vertex[v]) == outdegree[v]);
        }
    }   
}


#endif /* GRAPHTEST_H */

