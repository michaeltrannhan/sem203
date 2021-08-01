/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorterTest.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 11:03 PM
 */

#ifndef TOPOSORTERTEST_H
#define TOPOSORTERTEST_H

#include "doctest.h"
#include "graph/DGraphModel.h"
#include "graph/TopoSorter.h"


TEST_CASE( "TopoSort with DGraphModel" ) {
    int nv = 10, ne = 14;
    char vertex[]   = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char from[]     = {'0', '0', '1', '3', '3', '3', '3', '4', '6', '6', '6', '8', '8', '9'};
    char to[]       = {'1', '5', '7', '2', '4', '7', '8', '8', '0', '1', '2', '2', '7', '4'};
    char bfs_exp[]  = {'3', '6', '9', '0', '4', '1', '5', '8', '2', '7'};
    char dfs_exp[]  = {'3', '6', '0', '5', '1', '9', '4', '8', '2', '7'};

    DGraphModel<char> model(&charComparator, &vertex2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    for(int v=0; v < nv; v++) model.add(vertex[v]);
    for(int e=0; e < ne; e++) model.connect(from[e], to[e]);
    REQUIRE(model.size() == nv);
    
    TopoSorter<char> sorter(&model);
    DLinkedList<char> bfs = sorter.sort(TopoSorter<char>::BFS);
    DLinkedList<char>::Iterator it;
    
    int v= 0;
    for(it = bfs.begin(); it != bfs.end(); it++){
        REQUIRE(*it == bfs_exp[v++]);
    }
    
    v = 0;
    DLinkedList<char> dfs = sorter.sort(TopoSorter<char>::DFS);
    for(it = dfs.begin(); it != dfs.end(); it++){
        REQUIRE(*it == dfs_exp[v++]);
    }
}

#endif /* TOPOSORTERTEST_H */

