/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTest.h
 * Author: LTSACH
 *
 * Created on 13 September 2020, 11:11
 */

#ifndef AVLTEST_H
#define AVLTEST_H

#include "doctest.h"
#include "tree/AVL.h"

TEST_CASE( "AVL<int, int*>: adding items" ) {
    AVL<int, int*> tree;
    REQUIRE(tree.empty() == true);
    
    SUBCASE("Adding => no re-balance"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        REQUIRE(tree.height() == 3);
        tree.clear();
        REQUIRE(tree.empty() == true);
        REQUIRE(tree.height() == 0);
    }
    SUBCASE("Simple tree: LHoLH => rotateRight"){
        int keys[] = {50, 40, 30};
        string bfactor_exp[] = {sEH, sEH, sEH};
        for(int idx=0; idx < 3; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);
        
        DLinkedList<string> factor = tree.bfactor();
        REQUIRE(factor.size() == 3);
        REQUIRE(factor.contains(bfactor_exp, 3) == true);
    }
    SUBCASE("Simple tree: RHoLH => rotateLeft, then rotateRight"){
        int keys[] = {50, 30, 40};
        string bfactor_exp[] = {sEH, sEH, sEH};
        for(int idx=0; idx < 3; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);
        
        DLinkedList<string> factor = tree.bfactor();
        REQUIRE(factor.size() == 3);
        REQUIRE(factor.contains(bfactor_exp, 3) ==true);
    }
    SUBCASE("Simple tree: RHoRH => rotateLeft"){
        int keys[] = {30, 40, 50};
        string bfactor_exp[] = {sEH, sEH, sEH};
        for(int idx=0; idx < 3; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);
        
        DLinkedList<string> factor = tree.bfactor();
        REQUIRE(factor.size() == 3);
        REQUIRE(factor.contains(bfactor_exp, 3) == true);
    }
    SUBCASE("Simple tree: LHoRH => rotateRight, then rotateLeft"){
        int keys[] = {30, 50, 40};
        string bfactor_exp[] = {sEH, sEH, sEH};
        for(int idx=0; idx < 3; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);
        
        DLinkedList<string> factor = tree.bfactor();
        REQUIRE(factor.size() == 3);
        REQUIRE(factor.contains(bfactor_exp, 3) == true);
    }
    SUBCASE("LH-of-LH: more"){
        AVL<int, int*> tree;
        int keys1[] = {50, 40, 60, 30, 45, 20};
        int nodes_exp1[] = {40, 30, 50, 20, 45, 60};
        string bfactor_exp1[] = {sEH, sLH, sEH, sEH, sEMPTY, sEH, sEH}; 
        int keys2[] = {50, 40, 60, 30, 45, 35};
        int nodes_exp2[] = {40, 30, 50, 35, 45, 60};
        string bfactor_exp2[] = {sEH, sRH, sEH, sEMPTY, sEH, sEH, sEH}; 
        
        for(int idx=0; idx < 6; idx++) tree.add(keys1[idx] );
        List<string> factor1 = tree.bfactor();
        REQUIRE(factor1.size() == 7);
        REQUIRE(tree.height() == 3);
        REQUIRE(factor1.contains(bfactor_exp1, 7) == true);
        List<int> nodes1 = tree.bfsKey();
        REQUIRE(nodes1.size() == 6);
        REQUIRE(nodes1.contains(nodes_exp1, 6) == true);
        
        tree.clear();
        
        for(int idx=0; idx < 6; idx++) tree.add(keys2[idx] );
        List<string> factor2 = tree.bfactor();
        REQUIRE(factor2.size() == 7);
        REQUIRE(tree.height() == 3);
        REQUIRE(factor2.contains(bfactor_exp2, 7) == true);
        List<int> nodes2 = tree.bfsKey();
        REQUIRE(nodes2.size() == 6);
        REQUIRE(nodes2.contains(nodes_exp2, 6) == true);
    }
    
    SUBCASE("RH-of-LH: more"){
        AVL<int, int*> tree;
        int keys1[] = {50, 30, 60, 20, 40, 35};
        int nodes_exp1[] = {40, 30, 50, 20, 35, 60};
        string bfactor_exp1[] = {sEH, sEH, sRH, sEH, sEH, sEMPTY, sEH};
        
        for(int idx=0; idx < 6; idx++) tree.add(keys1[idx]);
        List<string> factor1 = tree.bfactor();
        
        REQUIRE(factor1.size() == 7);
        REQUIRE(factor1.contains(bfactor_exp1, 7) == true);
        List<int> nodes1 = tree.bfsKey();
        REQUIRE(nodes1.size() == 6);
        REQUIRE(nodes1.contains(nodes_exp1, 6) == true);
    }
    SUBCASE("RH-of-LH: more"){
        AVL<int, int*> tree;
        int keys1[] = {50, 30, 60, 20, 40, 45};
        int nodes_exp1[] = {40, 30, 50, 20, 45, 60};
        string bfactor_exp1[] = {sEH, sLH, sEH, sEH, sEMPTY, sEH, sEH}; 
   
        for(int idx=0; idx < 6; idx++) tree.add(keys1[idx]);
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 7);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 6);
        
    }
    SUBCASE("RH-of-RH: more"){
        AVL<int, int*> tree;
        int keys1[] = {50, 40, 70, 60, 80, 90};
        int nodes_exp1[] = {70, 50, 80, 40, 60, 90};
        string bfactor_exp1[] = {sEH, sEH, sRH, sEH, sEH, sEMPTY, sEH};
        int keys2[] = {50, 40, 70, 60, 80, 75};
        int nodes_exp2[] = {70, 50, 80, 40, 60, 75};
        string bfactor_exp2[] = {sEH, sEH, sRH, sEH, sEH, sEH, sEMPTY};
        
   
        for(int idx=0; idx < 6; idx++) tree.add(keys1[idx]);
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 7);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 6);
        
        tree.clear();
        for(int idx=0; idx < 6; idx++) tree.add(keys2[idx]);
        List<string> factor2 = tree.bfactor();
        factor2.contains(bfactor_exp2, 7);
        List<int> nodes2 = tree.bfsKey();
        nodes2.contains(nodes_exp2, 6);
    }
    SUBCASE("LH-of-RH: more"){
        AVL<int, int*> tree;
        int keys1[] = {50, 40, 80, 70, 90, 60};
        int nodes_exp1[] = {70, 50, 80, 40, 60, 90};
        string bfactor_exp1[] = {sEH, sEH, sRH, sEH, sEH, sEMPTY, sEH};
        int keys2[] = {50, 40, 80, 70, 90, 75};
        int nodes_exp2[] = {70, 50, 80, 40, 75, 90};
        string bfactor_exp2[] = {sEH, sLH, sEH, sEH, sEMPTY, sEH, sEH};
        
   
        for(int idx=0; idx < 6; idx++) tree.add(keys1[idx]);
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 7);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 6);
        
        tree.clear();
        for(int idx=0; idx < 6; idx++) tree.add(keys2[idx]);
        List<string> factor2 = tree.bfactor();
        factor2.contains(bfactor_exp2, 7);
        List<int> nodes2 = tree.bfsKey();
        nodes2.contains(nodes_exp2, 6);
    }
}
TEST_CASE( "AVL<int, int*>: removing items" ) {
    AVL<int, int*> tree;
    REQUIRE(tree.empty() == true);
    
    SUBCASE("Removing: unsuccess"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(999);
        REQUIRE(tree.size() == 7);
    }
    SUBCASE("Removing => no re-balance"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(20);
        REQUIRE(tree.size() == 6);
        
        tree.remove(40);
        REQUIRE(tree.size() == 5);
        
        int nodes_exp1[] = {50, 30, 70, 60, 80};
        string bfactor_exp1[] = {sEH, sEH, sEH, sEH, sEH};
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 5);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 5);
    }
    SUBCASE("Removing: EH-of-RH => single rotation: rotateLeft"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(20);
        tree.remove(40);
        tree.remove(30);
        REQUIRE(tree.size() == 4);
        
        int nodes_exp1[] = {70, 50, 80, 60};
        string bfactor_exp1[] = {sLH, sRH, sEH, sEMPTY, sEH};
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 4);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 5);
    }
    SUBCASE("Removing: simple RH-of-LH => double rotation"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(20);
        tree.remove(40);
        tree.remove(30);
        tree.remove(80);
        
        int nodes_exp1[] = {50, 60, 70};
        string bfactor_exp1[] = {sEH, sEH, sEH};
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 3);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 3);
    }
    SUBCASE("Removing: EH-of-LH => single rotation: rotateRight"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(60);
        tree.remove(80);
        tree.remove(70);
        REQUIRE(tree.size() == 4);
        
        int nodes_exp1[] = {30, 20, 50, 40};
        string bfactor_exp1[] = {sRH, sEH, sLH, sEH};
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 4);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 4);
    }
    SUBCASE("Removing: simple LH-of-RH => double rotation"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 7);
        
        tree.remove(60);
        tree.remove(80);
        tree.remove(70);
        tree.remove(20);
        
        int nodes_exp1[] = {30, 40, 50};
        string bfactor_exp1[] = {sEH, sEH, sEH};
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 3);
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 3);
    }
    SUBCASE("Removing: left not null; leaf node"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 65, 75};
        for(int idx=0; idx < 11; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 11);
        REQUIRE(tree.height() == 4);
        
        int removeKeys[] = {40, 35};
        for(int idx=0; idx < 2; idx++) tree.add(removeKeys[idx]);
        int nodes_exp1[] = {50, 25, 70, 20, 30, 60, 80, 65, 75};
        string bfactor_exp1[] = {sRH, sEH, sEH, sEH, sEH, sRH, sLH, sEMPTY, sEH, sEH, sEMPTY};
        
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 9);
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 11);
        
    }
    SUBCASE("Removing: right not null; leaf node"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 65, 75};
        for(int idx=0; idx < 11; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 11);
        
        int removeKeys[] = {60, 65};
        for(int idx=0; idx < 2; idx++) tree.add(removeKeys[idx]);
        int nodes_exp1[] = {50, 30, 75, 20, 40, 70, 80, 25, 35};
        string bfactor_exp1[] = {sLH, sEH, sEH, sRH, sLH, sEH, sEH, sEMPTY, sEH, sEH, sEMPTY};
        
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 9);
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 11);
        
    }
    SUBCASE("Removing: left+right not null"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 65, 75};
        for(int idx=0; idx < 11; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 11);
        
        tree.remove(50);
        
        int nodes_exp1[] = {50, 30, 70, 20, 35, 60, 80, 25, 65, 75};
        string bfactor_exp1[] = {sEH, sLH, sEH, sRH, sEH, sRH, sLH, sEMPTY, sEH, sEMPTY, sEH, sEH, sEMPTY};
        
        List<int> nodes1 = tree.bfsKey();
        nodes1.contains(nodes_exp1, 10);
        
        List<string> factor1 = tree.bfactor();
        factor1.contains(bfactor_exp1, 13);
        
    }
    SUBCASE("Removing: until emtpy"){
        int keys[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 65, 75};
        for(int idx=0; idx < 11; idx++) tree.add(keys[idx]);
        REQUIRE(tree.size() == 11);
        for(int idx=0; idx < 11; idx++) tree.remove(keys[idx]);
        REQUIRE(tree.size() == 0);
        
        List<int> nodes1 = tree.bfsKey();
        REQUIRE(nodes1.empty() == true);
        List<string> factor1 = tree.bfactor();
        REQUIRE(factor1.empty() == true);
    }
}
#endif /* AVLTEST_H */

