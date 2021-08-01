#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "list/XArrayList.h"
#include "list/SLinkedList.h"
#include "list/DLinkedList.h"
#include "list/IList.h"
#include "util/ArrayLib.h"
#include <algorithm>

int main()
{
    fstream fout;
    // fin.open("dlisttime.csv", ios::in);
    int nsizes = 100;
    int *ptr_sizes = genIntArray(2, 1, 1000000);
    DLinkedList<int> *list  = new DLinkedList<int>[2];
    //cout << "size of int  " << sizeof(int) << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int a = 0; a < ptr_sizes[i]; a++)
        {
            list[i].add(a);
        }
        for (auto size = 0; size < 100; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            list[i].add(0, 10);
            auto end = chrono::high_resolution_clock::now();
            double diff = end - start;
            cout << "time = " << diff << endl;
            fout 
        }
    }
    delete[] list;
    return 0;
}