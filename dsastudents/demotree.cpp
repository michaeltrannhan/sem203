#include <iostream>
#include <iomanip>
#include "list/DLinkedList.h"
#include "tree/AVL.h"
#include "tree/BST.h"
#include "tree/IBST.h"
#include "tree/ITreeWalker.h"
#include "util/Point.h" 
#include "util/ArrayLib.h"
#include "geom/Point3D.h"
#include "geom/Vector3D.h"
using namespace std;

void tree_quiz(){
    int size = 10;
    Point3D* ptr = Point3D::genPoints(10);
    BST<float, Point3D*> tree;
    for(int idx=0; idx < size; idx++) tree.add(ptr[idx].radius(), new Point3D(ptr[idx]));
    delete []ptr;
    tree.println();
}

void tree_quiz1(){
    int size = 10;
    Point3D* ptr = Point3D::genPoints(10);
    BST<float, Point3D*> tree;
    for(int idx=0; idx < size; idx++) tree.add(ptr[idx].radius(), new Point3D(ptr[idx]));
    tree.println();
}
void tree_quiz2(){
    int size = 10;
    Point3D* ptr = Point3D::genPoints(10);
    BST<float, Point3D*> tree;
    for(int idx=0; idx < size; idx++) tree.add(ptr[idx].radius(), &ptr[idx]);
    tree.println();
}
string value2str(int*& v){
    stringstream os;
    os << *v;
    return os.str().c_str();
}
void tree_quiz3(){
    int ptr[] = {50, 20, 80, 40, 60, 45};
    BST<int, int*> tree;
    for(int key: ptr) tree.add(key, new int(2*key));
    DLinkedList<int*> bfs = tree.bfs(); bfs.println(&value2str);
    DLinkedList<int*> dfs = tree.dfs(); dfs.println(&value2str);
    DLinkedList<int*> lnr = tree.lnr(); lnr.println(&value2str);
    DLinkedList<int*> nlr = tree.nlr(); nlr.println(&value2str);
    DLinkedList<int*> lrn = tree.lrn(); lrn.println(&value2str);
}
void tree_quiz4(){
    int ptr[] = {50, 20, 80, 40, 60, 45};
    AVL<int, int*> tree;
    for(int key: ptr) tree.add(key, new int(2*key));
    DLinkedList<int*> bfs = tree.bfs(); bfs.println(&value2str);
    DLinkedList<int*> dfs = tree.dfs(); dfs.println(&value2str);
    DLinkedList<int*> lnr = tree.lnr(); lnr.println(&value2str);
    DLinkedList<int*> nlr = tree.nlr(); nlr.println(&value2str);
    DLinkedList<int*> lrn = tree.lrn(); lrn.println(&value2str);
}
string node2str(int k, int* v){
    stringstream os;
    os << *v;
    return os.str().c_str();
}
// void tree_quiz5(){
//     int ptr[] = {50, 20, 80, 40, 60, 45};
//     BST<int, int*> tree;
//     for(int key: ptr) tree.add(key, new int(2*key));
//     tree.println(node2str());
// }
// string value2str(int*& value){
//     stringstream os;
//     os << *value;
//     return os.str();
// }
void demo_AVL1(){
    AVL<int, int*> tree;
    for(int i = 0; i < 10; i++) tree.add(i, new int(2*i));
    bool success = false;
    tree.remove(12,&success);
    cout << "state" << success << endl;
    tree.println();
}
void demo_AVL2(){
    AVL<int, int*> tree;
    
        int keys[] = {50, 30, 70, 20, 40, 60, 80};
        
        for(int idx=0; idx < 7; idx++) tree.add(keys[idx]);
        cout << tree.size() << endl;
        tree.remove(999);
        cout << tree.size() << endl;
}
int main(){
    demo_AVL2();
    
    return 0;
}