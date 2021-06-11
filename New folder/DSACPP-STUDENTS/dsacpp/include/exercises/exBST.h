/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exBST.h
 * Author: LTSACH
 *
 * Created on 1 September 2020, 16:42
 */

#ifndef EXBST_H
#define EXBST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

#include "tree/BST.h"
#include "list/XArrayList.h"

struct Node{
    int key;
    int* value;
    Node *left, *right;
    
    Node(int key=0, int* value=0, Node* left=0, Node* right=0){
        this->key = key;
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

/*
                            40
                        -----------
                       /           \
                      30            60
                   -------         ----- 
                  /       \       /     \
                20        35     55      80
                                /
                               50
  
 
*/

Node* sampleTree(){
    int key[] = {40, 30, 60, 20, 35, 55, 80, 50};
               //0   1   2   3   4   5   6   7
    Node** p = new Node*[8];
    for(int idx=0; idx < 8; idx++) p[idx] = new Node(key[idx]);
    p[0]->left = p[1];
    p[0]->right = p[2];
    p[1]->left = p[3];
    p[1]->right = p[4];
    p[2]->left = p[5];
    p[2]->right = p[6];
    p[5]->left = p[7];
    delete []p;
    return p[0];
}

/*
                            40
                        -----------
                       /           \
                      30            60
                   -------         ----- 
                  /       \       /     \
                20        35     55      80
                                /
                               50
                              /
                             45
  
 
*/
Node* sampleTree2(){
    int key[] = {40, 30, 60, 20, 35, 55, 80, 50, 45};
               //0   1   2   3   4   5   6   7   8
    Node** p = new Node*[9];
    for(int idx=0; idx < 9; idx++) p[idx] = new Node(key[idx]);
    p[0]->left = p[1];
    p[0]->right = p[2];
    p[1]->left = p[3];
    p[1]->right = p[4];
    p[2]->left = p[5];
    p[2]->right = p[6];
    p[5]->left = p[7];
    p[7]->left = p[8];
    delete []p;
    return p[0];
}
void deleteTree(Node* root){
    if(root == 0) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int height(Node* root){
    if(root == 0) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    
    if( lh > rh )return 1 + lh;
    else return 1 + rh;
}

bool isBalanced_(Node* root, int& height){
    if(root == 0){
        height = 0;
        return true;
    }
    int leftH, rightH;
    bool leftB = isBalanced_(root->left, leftH);
    bool rightB = isBalanced_(root->right, rightH);
    height = 1 + ((leftH > rightH) ? leftH : rightH); 
    return leftB && rightB && (abs(leftH - rightH) <=1);
}
bool isBalanced(Node* root){
    int height;
    return isBalanced_(root, height);
}
void numNodesInLevels_(Node* root, int levelOfRoot, int* num_nodes){
    if(root == 0) return;
    
    num_nodes[levelOfRoot] += 1;
    numNodesInLevels_(root->left, levelOfRoot + 1, num_nodes);
    numNodesInLevels_(root->right, levelOfRoot + 1, num_nodes);
}
XArrayList<int> numNodesInLevels(Node* root){
    XArrayList<int> list;
    int height_ = height(root);
    int* num_nodes = new int[height_];
    numNodesInLevels_(root, 0, num_nodes);
    for(int idx=0; idx < height_; idx++) list.add(num_nodes[idx]);
    delete []num_nodes;
    
    return list;
}
int numLeaves(Node* root){
    if(root == 0) return 0;
    if((root->left == 0) && (root->right == 0)) return 1;
    else{
        return numLeaves(root->left) + numLeaves(root->right);
    }
}

void getLeaves(Node* root, XArrayList<int>& list){
    if(root == 0) return;
    
    if((root->left == 0) && (root->left == 0))
        list.add(root->key);
    getLeaves(root->left, list);
    getLeaves(root->right, list);
}


void smallerThanKey(Node* root, int key, XArrayList<int>& list ){
    if(root == 0) return;
    if(key < root->key) smallerThanKey(root->left, key, list);
    else {
        smallerThanKey(root->left, key, list);
        list.add(root->key);
        smallerThanKey(root->right, key, list); //may have some key the same
    }
}

void keyInRange(Node* root, int min, int max, XArrayList<int>& list ){
    if(root == 0) return;
    if(root->key < min) keyInRange(root->right, min, max, list);
    else if(root->key == min){
        //key: == min
        list.add(root->key);
        keyInRange(root->right, min, max, list);
    }
    else if(root->key <= max){
        // key: (min, max]
        keyInRange(root->left, min, max, list);
        list.add(root->key);
        keyInRange(root->right, min, max, list);
    }
    else{
        //key: (max, inf)
        keyInRange(root->left, min, max, list);
    }
}
//
void bstHeight(){
    Node* root = sampleTree();
    cout << "Height: " << height(root) << endl;
    deleteTree(root);
}

void bstNumLeaves(){
    Node* root = sampleTree();
    cout << "#Leaves: " << numLeaves(root) << endl;
    deleteTree(root);
}
void bstListOfLeaves(){
    Node* root = sampleTree();
    XArrayList<int> leaves;
    getLeaves(root, leaves);
    cout << "Leaves: " << leaves.toString() << endl;
    deleteTree(root);
}
void bstSmallerThanKey(){
    Node* root = sampleTree();
    XArrayList<int> list;
    smallerThanKey(root, 50, list);
    cout << list.toString() << endl;
    deleteTree(root);
}
void bstKeyInRange(){
    Node* root = sampleTree();
    XArrayList<int> list;
    keyInRange(root, 33, 54, list);
    cout << list.toString() << endl;
    deleteTree(root);
}
void bstBalanced(){
    Node* root = sampleTree2();
    bool balanced = isBalanced(root);
    if(balanced) cout << "Tree is balanced" << endl;
    else cout << "Tree is imbalanced" << endl;
    deleteTree(root);
}
void bstNumNodesInLevels(){
    Node* root = sampleTree2();
    XArrayList<int> list = numNodesInLevels(root);
    cout << list.toString() << endl;
    deleteTree(root);
}

#include <math.h>
#include "util/Point.h"
#include "tree/BST.h"
#include "list/DLinkedList.h"

void bstPointList(){
    int nPoints = 10;
    Point* chain = Point::genPoints(nPoints, -10, 10);
    BST<float, Point*> tree;
    for(int idx =0; idx < nPoints; idx++){
        Point* p = new Point(chain[idx]);
        tree.add(p->radius(), p);
    }
    delete []chain;
    
    cout << tree.toString() << endl;
    
    DLinkedList<Point*> list = tree.ascendingList();
    for(DLinkedList<Point*>::Iterator it=list.begin(); it != list.end(); it++){
        Point* p = *it;
        cout << p->radius() << ", ";
    }
    cout << endl;
    
    
    list = tree.select(2, 5);
    for(DLinkedList<Point*>::Iterator it=list.begin(); it != list.end(); it++){
        Point* p = *it;
        cout << p->radius() << ", ";
    }
    cout << endl;
    
}
#endif /* EXBST_H */

