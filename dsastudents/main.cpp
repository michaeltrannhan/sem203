// #include <iostream>
// #include <iomanip>
// #include "list/SLinkedList.h"
// #include "list/IList.h"
// #include "geom/Point3D.h"
// #include "geom/Vector3D.h"
// #include "util/Point.h"
// #include "util/ArrayLib.h"
// void removeItemDataD(Point* p){
//     delete p;
// }
// int main(){
//     SLinkedList<Point*> list(&SLinkedList<Point*>::free, &Point::pointEQ);
//     list.add(new Point(1,1));
//     list.add(new Point(2,2));
//     list.add(new Point(3,3));
//     list.println();
//     cout << "---------" << endl;
//     Point *p = new Point(1,1);
//     cout << list.removeItem(p, &removeItemDataD);
//     return 0;
// }

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListDemo.h
 * Author: LTSACH
 *
 * Created on 19 August 2020, 21:16
 */


#include <iostream>
#include <iomanip>
#include "list/SLinkedList.h"
#include "util/Point.h"
using namespace std;

void slistDemo1(){
    SLinkedList<int> slist;
    for(int i = 0; i< 20 ; i++)
        slist.add(i*i);
    slist.println();
}
void slistDemo2(){
    SLinkedList<Point*> list1(&SLinkedList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));  
    list1.add(new Point(12.5f, 22.3f)); 
    
    for(SLinkedList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;
    
    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    cout << *p1 << "=> " << (list1.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list1.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p2) << endl;
    
    ///Different results if not pass &Point::equals
    cout << endl << endl;
    SLinkedList<Point*> list2(&SLinkedList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));  
    list2.add(new Point(12.5f, 22.3f)); 
    
    for(SLinkedList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;
    
    cout << *p1 << "=> " << (list2.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list2.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p2) << endl;
    
    delete p1; delete p2;
}
int main(){
    slistDemo2(); 
    return 0;
}

