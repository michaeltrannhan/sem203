#include <iostream>
#include <iomanip>
#include <list/XArrayList.h>
#include "list/SLinkedList.h"
#include "list/DLinkedList.h"
#include "util/Point.h"
#include "util/ArrayLib.h"
#include "chrono"
#include "vector"
using namespace std::chrono;
using namespace std;
void dlistDemo1()
{
    List<int> dlist;
    for (int i = 0; i < 20; i++)
    {
        dlist.add(i, i * i);
        cout << "index is: " << dlist.indexOf(i * i) << endl;
        cout << "item is: " << dlist.get(i) << endl;
    }
    dlist.println();

    for (List<int>::Iterator it = dlist.begin(); it != dlist.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void dlistDemo2()
{
    DLinkedList<Point *> list1(&DLinkedList<Point *>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));
    list1.add(new Point(12.5f, 22.3f));

    for (DLinkedList<Point *>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;

    Point *p1 = new Point(24.6f, 23.1f);  //found in list
    Point *p2 = new Point(124.6f, 23.1f); //not found
    cout << *p1 << "=> " << (list1.contains(p1) ? "found; " : "not found; ")
         << " indexOf returns: " << list1.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list1.contains(p2) ? "found; " : "not found; ")
         << " indexOf returns: " << list1.indexOf(p2) << endl;

    ///Different results if not pass &Point::equals
    cout << endl
         << endl;
    DLinkedList<Point *> list2(&DLinkedList<Point *>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));
    list2.add(new Point(12.5f, 22.3f));

    for (DLinkedList<Point *>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;

    cout << *p1 << "=> " << (list2.contains(p1) ? "found; " : "not found; ")
         << " indexOf returns: " << list2.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list2.contains(p2) ? "found; " : "not found; ")
         << " indexOf returns: " << list2.indexOf(p2) << endl;

    delete p1;
    delete p2;
}

void gentime()
{
    DLinkedList<int> dlist;
    for (auto size = 0; size < 100; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        //for(int i = 0; i < 626654; i++)
            dlist.add((int)(rand()),10);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end- start;
        cout << "time = " << diff.count() << endl;
    }
}

int main(){
    //gentime();
    // XArrayList<int> list1;
    // list1.add(2, 11); //* them vao vi tri so 2 gia tri 11
    // cout << "listsize: " << list1.size() << endl;
    // list1.println();
    // return 0;
    int nsizes =20;
    int max_length = 100;
    SLinkedList<int> list;
    cout << "list size : " << list.size();

    int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
    for(int idx=0; idx < nsizes; idx++){
        list.clear();
        
        int size = sizes[idx];
        int* items = genIntArray(size, -500, 500, true, 2021);
        
        //enforce removals: success
        for(int i=0; i < size; i++) list.add(items[i]);
        for(int i=0; i < size; i++){
            bool code = list.removeItem(items[i]);
            cout << "status : " << code << endl;
        }
        
        //enforce removals: fail
        for(int i=0; i < size; i++) list.add(items[i]);
        
        int notfound[] = {-5000, -4000, -1000, 1000, 3000, 5000}; 
        for(int item: notfound){
            bool code = list.removeItem(item);
            //cout << "status : " << code << endl;
        }
        delete []items;
    }
    delete []sizes; 
}