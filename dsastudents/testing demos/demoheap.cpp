#include <iostream>
#include <iomanip>
#include "heap/Heap.h"
#include "util/sampleFunc.h"
#include "util/Point.h"

using namespace std;

int myIntComparator(int& lhs, int& rhs){
    if(lhs < rhs) return +1;
    else if(lhs > rhs) return -1;
    else return 0;
}
void anotherHeap(){
    Heap<int> heap;
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
    for(int idx =0; idx < 8; idx++) heap.push(array[idx]);
    heap.println();
    heap.pop();
    heap.println();
    heap.push(5);
    heap.println();
    
    Heap<int> maxHeap(&myIntComparator);
    for(int idx =0; idx < 8; idx++) maxHeap.push(array[idx]);
    maxHeap.println();
    maxHeap.pop();
    maxHeap.println();
    maxHeap.push(70);
    maxHeap.println();
    
    
}
void simpleMinHeap(){
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
              //    0   1   2   3  4  5  6   7
    //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
    //[6,10,7,23,15,20,8,50]

    cout << "Input array: ";
    for(int idx =0; idx < 8; idx++) cout << array[idx]  << "  ";
    cout << endl;
    
    Heap<int> minHeap;
    for(int idx =0; idx < 8; idx++){
        minHeap.clear();
        minHeap.heapify(array, idx+1);
        cout << "Min heap: " << minHeap.toString() << endl;
    }
    const int& a = minHeap.peek();
    cout << "a = " << a << endl;
}

void heapDemo1(){
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
    //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
    //max heap: [50, 23, 15, 20, 8, 6, 7, 10]
    Heap<int> minHeap1;
    cout << "Min Heap: ";
    minHeap1.heapify(array, 8);
    cout << minHeap1.toString() << endl;
    
    Heap<int> minHeap2(minHeapComparator);
    cout << "Min Heap: ";
    minHeap2.heapify(array, 8);
    cout << minHeap2.toString() << endl;
    
    Heap<int> maxHeap(maxHeapComparator);
    cout << "Max Heap: ";
    maxHeap.heapify(array, 8);
    cout << maxHeap.toString() << endl;
}

void heapDemo2(){
    Point array[] = {
        Point(13.1, 12.4), Point(5.5, 4.5), Point(15.5, 14.5),
        Point(23.1, 12.4), Point(35.5, 14.5), Point(5.5, 34.5)
    };
    Heap<Point> minHeap1(minHeapComparator);
    cout << "Min Heap: ";
    minHeap1.heapify(array, 6);
    cout << minHeap1.toString(&point2str) << endl;
    
    Heap<Point> maxHeap(maxHeapComparator);
    cout << "Max Heap: ";
    maxHeap.heapify(array, 6);
    cout << maxHeap.toString(&point2str) << endl;
}

int myPointComparator(Point*&  lhs, Point*& rhs){
    if(lhs->radius() < rhs->radius()) return -1;
    else if(lhs->radius() > rhs->radius()) return +1;
    else return 0;
}
int myPointComparatorMAX(Point*&  lhs, Point*& rhs){
    if(lhs->radius() < rhs->radius()) return +1;
    else if(lhs->radius() > rhs->radius()) return -1;
    else return 0;
}

string myPoint2Str(Point*& point){
    stringstream os;
    os << "["   << setw(6) << setprecision(2) << point->getX() 
                << ", "
                << setw(6) << setprecision(2) << point->getY()
       << "]";
    return os.str();
}
void heapDemo3(){
    Point* array[] = {
        new Point(13.1, 12.4), new Point(5.5, 4.5), new Point(15.5, 14.5),
        new Point(23.1, 12.4), new Point(35.5, 14.5), new Point(5.5, 34.5)
    };
    Heap<Point*> heap(&myPointComparatorMAX, &Heap<Point*>::free);
    for(int idx=0; idx < 6; idx++) heap.push(array[idx]);
    heap.println(&myPoint2Str);
    
    for(Heap<Point*>::Iterator it = heap.begin(); it != heap.end(); it++){
        Point* point = *it;
        cout << point->radius() << ", ";
    }
    cout << endl;
}

void demo_1()
{
    Heap<int> minHeap; //need not passing &minComparator, default is min-heap
    // Heap<int> maxHeap(&maxHeapComparator);
    int item[] = {50, 20, 15, 10, 8, 6, 7, 23};
    // /// min-heap : heapify
    // minHeap.heapify(item, 8);
    // int minexp[] = {6, 10, 7, 23, 15, 20, 8, 50};
    // Heap<int>::Iterator it;
    // int idx = 0;
    // for (it = minHeap.begin(); it != minHeap.end(); it++)
    // {
    //     if (minexp[idx++] != *it)
    //         cout << "error!" << endl;
    // }
    // minHeap.clear();
    ///* end of first testcase
    //*min-heap :heapify / peek:
    int peek_exp[] = {6, 7, 8, 10, 15, 20, 23, 50};
    minHeap.heapify(item, 8);
    int idx = 0;
    while (!minHeap.empty())
    {
        cout << minHeap.peek() << "---" << peek_exp[idx] << endl;
        cout << minHeap.pop() << "---" << peek_exp[idx] << endl;
        idx++;
    }
}
int comparator(int& lhs, int& rhs){
    if(lhs < rhs) return +1;
    else if(lhs > rhs) return -1;
    else return 0;
}
void heap_quiz(){
    int ptr[] = {5, 90, 15, 20, 70, 5};
    Heap<int> heap(&comparator);
    heap.heapify(ptr, 6);
    for(; !heap.empty();){
        int v = heap.pop();
        cout << v << " ";
    }
}
int comparator1(int*& lhs, int*& rhs){
    if(*lhs < *rhs) return -1;
    else if(*lhs > *rhs) return +1;
    else return 0;
}

string item2str1(int*& item){
    stringstream os;
    os << *item;
    return os.str();
}

void heap_quiz1(){
    int ptr[] = {50, 20, 70, 5, 15, 80};
    Heap<int*> heap(&comparator1);
    for(int idx=0; idx< 6; idx++) heap.push(&ptr[idx]);
    heap.println(&item2str1);
}
int main()
{
    //demo_1();
//     Heap<int> minheap(&maxHeapComparator);
//     //Heap<int> minheap;
//     int array[] = {50,20,70,5,15,80};
//    // min heap: [6, 10, 7, 23, 15, 20, 8, 50]
//     int exp[] = {6, 10, 7, 23, 15, 20, 8, 50};


//     // int exp1[] = {6, 10, 7, 15, 20, 8, 50}; //after removing 23
//     //     int exp2[] = {6, 8, 7, 15, 10, 50}; //after removing 23, then 20
//     int peek_exp[] = {6, 7, 8, 10, 15, 20, 23, 50};
//     minheap.heapify(array, 6);
//     minheap.println();
//     cout << "--------------------"<< endl;
//     minheap.remove(45);
//     minheap.remove(75);
//     minheap.println();
heap_quiz1();
        return 0;
    //anotherHeap();
}