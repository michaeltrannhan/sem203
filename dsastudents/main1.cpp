#include <iostream>
#include <iomanip>
#include <list/XArrayList.h>
#include "list/DLinkedList.h"
#include "util/Point.h"
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

int main()
{
    // DLinkedList<int> list;
    // for(int i = 0; i < 5;i++){
    //     list.add(i);
    // }
    // list.add(3, 5);
    // list.removeAt(3);
    // list.println();
    // cout << endl;
    gentime();
    return 0;
}