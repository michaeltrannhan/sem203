#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <math.h>
using namespace std;
using namespace std::chrono;

#include "dsacpp/include/list/XArrayList1.h"
#include "dsacpp/include/list/SLinkedList1.h"
#include "dsacpp/include/list/DLinkedList1.h"
#include "dsacpp/include/list/IList.h"
#include "dsacpp/include/util/ArrayLib.h"



/*
NOTE:
  * SHOULD define other functions to support the implementation of "meter"
  * Parameters: read the explanation presented above
*/
double addFirst(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(0, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}

double addLast(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double addIndex(IList<int> *list, int randVal, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(randVal, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double removeFirst(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->removeAt(0);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double removeLast(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->removeAt(list->size() - 1);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double removeIndex(IList<int> *list, int randVal, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->removeAt(randVal);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double getIndex(IList<int> *list, int randVal, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->get(randVal);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double getFirstIndex(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->get(0);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double getLastIndex(IList<int> *list, int nexec)
{
    double total = 0;
    for (auto size = 0; size < nexec; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->get(list->size()-1);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}

void meter(IList<int>* plist, string csvfile, int *ptr_sizes, int nsizes, int nexec = 10, int ntries = 10)
{
    //YOUR CODE HERE
    fstream fout;
    fout.open(csvfile);
    fout << "size"
         << ","
         << "addfirst(ms)"
         << ","
         << "addlast(ms)"
         << ","
         << "addrandpos(ms)"
         << ","
         << "removefist(ms)"
         << ","
         << "removelast(ms)"
         << ","
         << "removerandpos(ms)"
         << ","
         << "getrandpos(ms)" 
         << ","
         << "getFirstpos(ms)"
         << ","
         << "getLastpos(ms)"
         << endl;
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(15) << setprecision(4) << "addFirst(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "addLast(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "addRand(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "removeFirst(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "removeLast(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "removeRand(ms)"
         << ", "
         << fixed << setw(15) << setprecision(4) << "getrand(ms)" 
         << ", "
         << fixed << setw(15) << setprecision(4) << "getFirst(ms)" 
         << ", "
         << fixed << setw(15) << setprecision(4) << "getLast(ms)" << endl;
    for (int i = 0; i < nsizes; i++)
    {
        for (int j = 0; j < ptr_sizes[i]; j++)
        {
            plist->add(j);
        }
        
        int size = ptr_sizes[i];
     
        double addfirst = addFirst(plist, nexec) / (nexec);
        double addlast = addLast(plist, nexec) / (nexec);
        double removefisrt = removeFirst(plist, nexec) / (nexec);
        double removelast = removeLast(plist, nexec) / (nexec);
        double getFirst = getFirstIndex(plist,nexec) / (nexec);
        double getLast = getLastIndex(plist, nexec) / (nexec);
        double addrand= 0, removerand = 0, getrand = 0;
        int k = ntries;
        while (k--){
            int randval = (rand() % static_cast<int>(ptr_sizes[i] - 1));
            addrand += addIndex(plist, randval, nexec);
            removerand += removeIndex(plist, randval, nexec);
            getrand += getIndex(plist, randval, nexec);
        }
        addrand /= (nexec * ntries);
        removerand /= (nexec * ntries);
        getrand /= (nexec * ntries);

        fout << size << "," << addfirst << "," << addlast << "," << addrand << "," << removefisrt << "," << removelast << "," << removerand << "," << getrand << "," << getFirst << "," << getLast << endl;
        if (i % 10 == 0)
        {
            cout << "[" << setw(2) << i << "/" << setw(3) << nsizes << "]"
                 << ":\t"
                 << ptr_sizes[i] << "\t->"
                 << fixed << setw(9) << setprecision(4) << addfirst << ", "
                 << fixed << setw(9) << setprecision(4) << addlast << ", "
                 << fixed << setw(9) << setprecision(4) << addrand << ", "
                 << fixed << setw(9) << setprecision(4) << removefisrt << ", "
                 << fixed << setw(9) << setprecision(4) << removelast << ", "
                 << fixed << setw(9) << setprecision(4) << removerand << ", "
                 << fixed << setw(9) << setprecision(4) << getrand << "," 
                 << fixed << setw(9) << setprecision(4) << getFirst << "," 
                 << fixed << setw(9) << setprecision(4) << getLast <<endl;
        }
        plist->clear();
    }
    fout.close();
    cout <<"Success!" << endl;
}

int get_int(char **begin, char **end, const string &option, int _default)
{
    char **ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end)
        return stoi(*ptr);
    else
        return _default;
}

string get_string(char **begin, char **end, const string &option, string _default)
{
    char **ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end)
        return string(*ptr);
    else
        return _default;
}
bool option_exist(char **begin, char **end, const string &option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char **argv)
{
    if (option_exist(argv, argv + argc, "-h"))
    {
        cout << "Show help" << endl;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////////
    int nsizes, nexec, max_length, ntries;
    XArrayList<int> alist;
    SLinkedList<int> slist;
    DLinkedList<int> dlist;

    nsizes = get_int(argv, argv + argc, "-nsizes", 50);
    nexec = get_int(argv, argv + argc, "-nexec", 20);
    max_length = get_int(argv, argv + argc, "-max_length", 1000);
    ntries = get_int(argv, argv + argc, "-ntries", 10);
    int *ptr_sizes = genIntArray(nsizes, 1, max_length);

    //cout << nsizes << ", " << nexec << ", " << max_length << ", " << ntries << endl;
    if (option_exist(argv, argv + argc, "-a"))
    {
        cout << endl;
        cout << "XArrayList: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv + argc, "-a", "");
        meter(&alist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if (option_exist(argv, argv + argc, "-s"))
    {
        cout << endl;
        cout << "SLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv + argc, "-s", "");
        meter(&slist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if (option_exist(argv, argv + argc, "-d"))
    {
        cout << endl;
        cout << "DLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv + argc, "-d", "");
        meter(&dlist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
}