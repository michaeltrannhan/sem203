#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <math.h>

#include "dsacpp/include/list/DLinkedList1.h"
#include "dsacpp/include/list/IList.h"
// #include "dsacpp/include/list/SLinkedList.h"
// #include "dsacpp/include/list/XArrayList.h"
#include "dsacpp/include/sorting/BubbleSort.h"
#include "dsacpp/include/sorting/DLinkedListSE.h"
#include "dsacpp/include/sorting/HeapSort.h"
#include "dsacpp/include/sorting/QuickSort.h"
#include "dsacpp/include/sorting/ShellSort.h"
#include "dsacpp/include/sorting/StraightInsertionSort.h"
#include "dsacpp/include/sorting/StraightSelectionSort.h"
// #include "dsacpp/include/sorting/XArrayListSE.h"
// #include "dsacpp/include/sorting/SLinkedListSE.h"
#include "dsacpp/include/sorting/ISort.h"
#include "dsacpp/include/geom/Point3D.h"
#include "dsacpp/include/geom/Vector3D.h"
#include "dsacpp/include/util/ArrayLib.h"
#include "dsacpp/include/util/FileIOLib.h"
#include "dsacpp/include/util/Point.h"
#include "dsacpp/include/heap/Heap.h"
#include "dsacpp/include/heap/IHeap.h"
using namespace std;
using namespace std::chrono;

double sort_best(ISort<int> *&list, int size)
{
    int* best_case = new int[size];
    for (int j = 0; j < size; j++)
    {
        best_case[j] = j;
    }
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list->sort(best_case, size, &SortSimpleOrder<int>::compare4Ascending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    delete best_case;
    return total;
    
}
double sort_best_dll(DLinkedListSE<int> list, int size)
{
    for (int j = 1; j <= size; j++)
    {
        list.add(j);
    }
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list.sort(&SortSimpleOrder<int>::compare4Ascending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    list.clear();
    return total;
    
}
double sort_random(ISort<int> *&list, int size)
{
    int *randVal = genIntArray(size, 0, 10000);
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list->sort(randVal, size, &SortSimpleOrder<int>::compare4Ascending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    delete randVal;
    return total;
    
}
double sort_random_dll(DLinkedListSE<int> list, int size)
{
    int *randVal = genIntArray(size, 0, 10000);
    for(int  i = 0; i < size; i++){
        list.add(randVal[i]);
    }
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list.sort(&SortSimpleOrder<int>::compare4Ascending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    list.clear();
    return total;
    
}

double sort_worst_dll(DLinkedListSE<int> list, int size)
{
    for (int j = 1; j <= size; j++)
    {
        list.add(j);
    }
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list.sort(&SortSimpleOrder<int>::compare4Desending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    list.clear();
    return total;
    
}
double sort_worst(ISort<int> *&list, int size)
{
    int* worst_case = new int[size];
    for (int j = 0; j < size; j++)
    {
        worst_case[j] = j;
    }
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    list->sort(worst_case, size, &SortSimpleOrder<int>::compare4Desending);
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    total += duration;
    delete worst_case;
    return total;
    
}

void meter_best(string csvfile, int *ptr_sizes, int nsizes)
{
    fstream fout;
    fout.open(csvfile,fstream::out);
    fout << "size"
         << ","
         << "StraightInsertionSort"
         << ","
         << "ShellSort"
         << ","
         << "StraightSelectionSort"
         << ","
         << "BubbleSort"
         << ","
         << "HeapSort"
         << ","
         << "QuickSort"
         << ","
         << "Merge sort - DLL"
         << endl;
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(20) << setprecision(4) << "StraightInsertion"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Shell"
         << ", "
         << fixed << setw(20) << setprecision(4) << "StraightSelection"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Bubble"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Heap"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Quick"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Merge"
         << endl;

    int shell_segments[] = {1, 3, 7};
    ISort<int> *pAlgorithm[] = {
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()};
    for (int i = 0; i < nsizes; i++)
    {
        // array for best case : sorted ascending
        DLinkedListSE<int> list;
        double SIS = sort_best(pAlgorithm[0], ptr_sizes[i]);

        double SS = sort_best(pAlgorithm[1], ptr_sizes[i]);

        double SSS = sort_best(pAlgorithm[2], ptr_sizes[i]);

        double BS = sort_best(pAlgorithm[3], ptr_sizes[i]);

        double HS = sort_best(pAlgorithm[4], ptr_sizes[i]);

        double QS = sort_best(pAlgorithm[5], ptr_sizes[i]);
        
        double MS = sort_best_dll(list, ptr_sizes[i]);

        fout << ptr_sizes[i]
             << "," << SIS
             << "," << SS
             << "," << SSS
             << "," << BS
             << "," << HS
             << "," << QS
             << "," << MS
             << endl;
        if (i % 10 == 0)
        {
            cout << "[" << setw(2) << i << "/" << setw(3) << nsizes << "]"
                 << ":\t"
                 << ptr_sizes[i] << "\t->"
                 << fixed << setw(20) << setprecision(4) << SIS << ", "
                 << fixed << setw(20) << setprecision(4) << SS << ", "
                 << fixed << setw(20) << setprecision(4) << SSS << ", "
                 << fixed << setw(20) << setprecision(4) << BS << ", "
                 << fixed << setw(20) << setprecision(4) << HS << ", "
                 << fixed << setw(20) << setprecision(4) << QS << ", "
                 << fixed << setw(20) << setprecision(4) << MS
                 << endl;
        }
    }

    for (int a = 0; a < 6; a++)
    {
        delete pAlgorithm[a];
    }
    fout.close();
    cout << "success!" << endl;
}
void meter_random(string csvfile, int *ptr_sizes, int nsizes)
{
    fstream fout;
    fout.open(csvfile,fstream::out);
    fout << "size"
         << ","
         << "StraightInsertionSort"
         << ","
         << "ShellSort"
         << ","
         << "StraightSelectionSort"
         << ","
         << "BubbleSort"
         << ","
         << "HeapSort"
         << ","
         << "QuickSort"
         << ","
         << "Merge sort - DLL"
         << endl;
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(20) << setprecision(4) << "StraightInsertion"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Shell"
         << ", "
         << fixed << setw(20) << setprecision(4) << "StraightSelection"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Bubble"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Heap"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Quick"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Merge"
         << endl;

    int shell_segments[] = {1, 3, 7};
    ISort<int> *pAlgorithm[] = {
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()};
    for (int i = 0; i < nsizes; i++)
    {
        // array for best case : sorted ascending
        DLinkedListSE<int> list;
        double SIS = sort_random(pAlgorithm[0], ptr_sizes[i]);

        double SS = sort_random(pAlgorithm[1], ptr_sizes[i]);

        double SSS = sort_random(pAlgorithm[2], ptr_sizes[i]);

        double BS = sort_random(pAlgorithm[3], ptr_sizes[i]);

        double HS = sort_random(pAlgorithm[4], ptr_sizes[i]);

        double QS = sort_random(pAlgorithm[5], ptr_sizes[i]);
        
        double MS = sort_random_dll(list, ptr_sizes[i]);

        fout << ptr_sizes[i]
             << "," << SIS
             << "," << SS
             << "," << SSS
             << "," << BS
             << "," << HS
             << "," << QS
             << "," << MS
             << endl;
        if (i % 10 == 0)
        {
            cout << "[" << setw(2) << i << "/" << setw(3) << nsizes << "]"
                 << ":\t"
                 << ptr_sizes[i] << "\t->"
                 << fixed << setw(20) << setprecision(4) << SIS << ", "
                 << fixed << setw(20) << setprecision(4) << SS << ", "
                 << fixed << setw(20) << setprecision(4) << SSS << ", "
                 << fixed << setw(20) << setprecision(4) << BS << ", "
                 << fixed << setw(20) << setprecision(4) << HS << ", "
                 << fixed << setw(20) << setprecision(4) << QS << ", "
                 << fixed << setw(20) << setprecision(4) << MS
                 << endl;
        }
    }

    for (int a = 0; a < 6; a++)
    {
        delete pAlgorithm[a];
    }
    fout.close();
    cout << "success!" << endl;
}
void meter_worst(string csvfile, int *ptr_sizes, int nsizes)
{
    fstream fout;
    fout.open(csvfile,fstream::out);
    fout << "size"
         << ","
         << "StraightInsertionSort"
         << ","
         << "ShellSort"
         << ","
         << "StraightSelectionSort"
         << ","
         << "BubbleSort"
         << ","
         << "HeapSort"
         << ","
         << "QuickSort"
         << ","
         << "Merge sort - DLL"
         << endl;
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(20) << setprecision(4) << "StraightInsertion"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Shell"
         << ", "
         << fixed << setw(20) << setprecision(4) << "StraightSelection"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Bubble"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Heap"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Quick"
         << ", "
         << fixed << setw(20) << setprecision(4) << "Merge"
         << endl;

    int shell_segments[] = {1, 3, 7};
    ISort<int> *pAlgorithm[] = {
        new StraightInsertionSort<int>(),
        new ShellSort<int>(shell_segments, 3),
        new StraightSelectionSort<int>(),
        new BubbleSort<int>(),
        new HeapSort<int>(),
        new QuickSort<int>()};
    for (int i = 0; i < nsizes; i++)
    {
        // array for best case : sorted ascending
        DLinkedListSE<int> list;
        double SIS = sort_worst(pAlgorithm[0], ptr_sizes[i]);

        double SS = sort_worst(pAlgorithm[1], ptr_sizes[i]);

        double SSS = sort_worst(pAlgorithm[2], ptr_sizes[i]);

        double BS = sort_worst(pAlgorithm[3], ptr_sizes[i]);

        double HS = sort_worst(pAlgorithm[4], ptr_sizes[i]);

        double QS = sort_worst(pAlgorithm[5], ptr_sizes[i]);
        
        double MS = sort_worst_dll(list, ptr_sizes[i]);

        fout << ptr_sizes[i]
             << "," << SIS
             << "," << SS
             << "," << SSS
             << "," << BS
             << "," << HS
             << "," << QS
             << "," << MS
             << endl;
        if (i % 10 == 0)
        {
            cout << "[" << setw(2) << i << "/" << setw(3) << nsizes << "]"
                 << ":\t"
                 << ptr_sizes[i] << "\t->"
                 << fixed << setw(20) << setprecision(4) << SIS << ", "
                 << fixed << setw(20) << setprecision(4) << SS << ", "
                 << fixed << setw(20) << setprecision(4) << SSS << ", "
                 << fixed << setw(20) << setprecision(4) << BS << ", "
                 << fixed << setw(20) << setprecision(4) << HS << ", "
                 << fixed << setw(20) << setprecision(4) << QS << ", "
                 << fixed << setw(20) << setprecision(4) << MS
                 << endl;
        }
    }

    for (int a = 0; a < 6; a++)
    {
        delete pAlgorithm[a];
    }
    fout.close();
    cout << "success!" << endl;
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

    int nsizes, nexec, max_length, ntries;
    nsizes = get_int(argv, argv + argc, "-nsizes", 50);
    nexec = get_int(argv, argv + argc, "-nexec", 20);
    max_length = get_int(argv, argv + argc, "-max_length", 1000);
    ntries = get_int(argv, argv + argc, "-ntries", 10);
    int *ptr_sizes = genIntArray(nsizes, 1, max_length);

    if (option_exist(argv, argv + argc, "-b"))
    {
        cout << endl;
        cout << "Time measurements for sorting algorithms - BEST CASE" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv + argc, "-b", " ");
        meter_best(filename, ptr_sizes, nsizes);
    }
    if (option_exist(argv, argv + argc, "-a"))
    {
        cout << endl;
        cout << "Time measurements for sorting algorithms - RANDOM CASE" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv + argc, "-a", " ");
        meter_random(filename, ptr_sizes, nsizes);
    }
    if (option_exist(argv, argv + argc, "-w"))
    {
        cout << endl;
        cout << "Time measurements for sorting algorithms - WORST CASE" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv + argc, "-w", " ");
        meter_worst(filename, ptr_sizes, nsizes);
    }
}