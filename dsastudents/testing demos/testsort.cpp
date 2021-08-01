#include <iostream>
#include <sorting/BubbleSort.h>
#include <sorting/ISort.h>
#include <util/sampleFunc.h>
#include <sorting/BubbleSortDemo.h>
#include <sorting/ShellSort.h>
#include <sorting/StraightInsertionSort.h>
#include <sorting/StraightInsertionSortDemo.h>
#include <sorting/ShellSortDemo.h>
#include <sorting/HeapSortDemo.h>
#include <heap/heap1.h>
#include <heap/IHeap.h>
#include <sorting/StraightSelectionSort.h>
#include <sorting/StraightSelectionSortDemo.h>
#include <sorting/DLinkedListSE.h>
#include <list/DLinkedList.h>
#include <list/IList.h>
#include <util/ArrayLib.h>
#include <util/Point.h>
#include <sorting/QuickSort.h>
#include <sorting/QuickSortDemo.h>
using namespace std;

int main(){
    HeapSort<int> heappp;
    int count = 1000;
    int *val = genIntArray(count, 0, 99999);
    heappp.sort(val, count);
    cout << "----" << endl;
    cout << isOrdered(val, count, true);

    return 0;
}