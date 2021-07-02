
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
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

double addFirst(IList<int> *list, int nexec, int ntries)
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

double addLast(IList<int> *list, int nexec, int ntries)
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
double addIndex(IList<int> *list, int randVal, int nexec, int ntries)
{
    double total = 0;
    for (auto size = 0; size < nexec * ntries; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(randVal, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double removeFirst(IList<int> *list, int nexec, int ntries)
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
    return total*;
}
double removeLast(IList<int> *list, int nexec, int ntries)
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
double removeIndex(IList<int> *list, int randVal, int nexec, int ntries)
{
    double total = 0;
    for (auto size = 0; size < nexec * ntries; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->removeAt(randVal);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}
double getIndex(IList<int> *list, int randVal, int nexec, int ntries)
{
    double total = 0;
    for (auto size = 0; size < nexec * ntries; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->get(randVal);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}

void meter(IList<int>* plist, string csvfile, int *ptr_sizes, int nsizes, int nexec = 10, int ntries = 10)
{
    //YOUR CODE HERE
    ofstream fout;
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
         << "getrandpos(ms)" << endl;
    //plist = new T[nsizes];
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(12) << setprecision(4) << "addFirst(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "addLast(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "addRand(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "removeFirst(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "removeLast(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "removeRand(ms)"
         << ", "
         << fixed << setw(12) << setprecision(4) << "getrand(ms)" << endl;
    for (int i = 0; i < nsizes; i++)
    {
        plist->clear();
        for (int j = 0; j < ptr_sizes[i]; j++)
        {
            plist->add(j);
        }
        int randval = (rand()% static_cast<int>(ptr_sizes[i]-1));
        int size = ptr_sizes[i];
        double addfirst = addFirst(plist, nexec, ntries) / (nexec);
        double addlast = addLast(plist, nexec, ntries) / (nexec);
        double addrand = addIndex(plist, randval, nexec, ntries) / (nexec * ntries);
        double removefisrt = removeFirst(plist, nexec, ntries) / (nexec);
        double removelast = removeLast(plist, nexec, ntries) / (nexec);
        double removerand = removeIndex(plist, randval, nexec, ntries) / (nexec * ntries);
        double getrand = getIndex(plist, randval, nexec, ntries) / (nexec * ntries);
        fout << size << "," << addfirst << "," << addlast << "," << addrand << "," << removefisrt << "," << removelast << "," << removerand << "," << getrand << endl;
        if (i % 10 == 0)
        {
            cout << "[" << setw(2) << i << "/" << setw(3) << nsizes << "]"
                 << ":\t"
                 << ptr_sizes[i] << "\t->"
                 << fixed << setw(12) << setprecision(4) << addfirst << ", "
                 << fixed << setw(12) << setprecision(4) << addlast << ", "
                 << fixed << setw(12) << setprecision(4) << addrand << ", "
                 << fixed << setw(12) << setprecision(4) << removefisrt << ", "
                 << fixed << setw(12) << setprecision(4) << removelast << ", "
                 << fixed << setw(12) << setprecision(4) << removerand << ", "
                 << fixed << setw(12) << setprecision(4) << getrand << endl;
        }
    }
    fout.close();
    //plist->clear();
    cout <<"Success!" << endl;
}


double add(IList<int>* plist, int i = -1, int k = 0, int pos = -1){
    double ret = 0;
    while (k--){   
          auto t1 = chrono::high_resolution_clock::now();
          if (pos == -1)//add last
            plist->add(i);
          else
            plist->add(pos, i); 
          auto t2 = chrono::high_resolution_clock::now();
          auto timeTaken = duration_cast<milliseconds>(t2 - t1);
          ret += timeTaken.count();
    }
    return ret;
}

double remove(IList<int>* plist, int k = 0, int pos = -1){
    double ret = 0;
    int cnt = k;
    int s = plist->size() - 1;
    while (k--){   
          auto t1 = chrono::high_resolution_clock::now();
          double temp;
          if (pos == -1)
            temp = plist->removeAt(s--);//remove last
          else
            temp = plist->removeAt(pos);
          auto t2 = chrono::high_resolution_clock::now();
          auto timeTaken = duration_cast<milliseconds>(t2 - t1);
          ret += timeTaken.count();
    }
    
    return ret;
}

double get(IList<int>* plist, int pos = 0, int k = 0){
    double ret = 0;
    while (k--){   
          auto t1 = chrono::high_resolution_clock::now();
          double temp = plist->get(pos); // add at first
          auto t2 = chrono::high_resolution_clock::now();
          auto timeTaken = duration_cast<milliseconds>(t2 - t1);
          ret += timeTaken.count();
    }
    return ret;
}


void meter2(IList<int>* plist, string csvfile, int* ptr_sizes, int nsizes,
           int nexec=10, int ntries=10){
    //YOUR CODE HERE
      fstream myFile;
      myFile.open(csvfile, ios::out | ios::app);
      myFile <<"size,addfirst,addlast,addrandpos,removefirst, removelast, removerandpos, getrandpos\n";
      
      cout << "idx/size"<< ":\t"<< "n"<< ":\t"
         << fixed << setw(12) << setprecision(4) << "addFirst(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "addLast(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "addRand(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "removeFirst(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "removeLast(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "removeRand(ms)"<< ", "
         << fixed << setw(12) << setprecision(4) << "getrand(ms)" << endl;
      
      int SIZEth = 0, row = 0;
      while (SIZEth != nsizes){
        int i = 0;
        int size = ptr_sizes[SIZEth];

        // create the list contains size elements
        while (i != size){
            plist->add(i++);
        }  

        double addF = 0, addL = 0, addR = 0, removeF = 0, removeL = 0, removeR = 0, gett = 0;
        i = 0;

        //add & remove item at the beginning of the list nexec times
        addF = add(plist, i--, nexec, 0);
        removeF = remove(plist, nexec, 0);

        //add & remove item at the last of the list nexec times
        addL = add(plist, i--, nexec);
        removeL = remove(plist, nexec);

        //add, get & remove item at the kth position of the list nexec times
        int IDXth = ntries;
        while (IDXth--){ 
          int idx =  (rand() % static_cast<int>(size - 1)); // generate random position that item will be added into              
          i--;
          addR    += add(plist, i, nexec, 0);//each idx randomly generated will be executed n
          gett    += get(plist, idx, nexec);
          removeR += remove(plist, nexec, idx);   
        }
        plist->clear(); // clear plist before generate the new one

        addF     /= (nexec)*pow(10,6);
        addL     /= (nexec)*pow(10,6);
        addR     /= (nexec*ntries)*pow(10,6);
        removeF  /= (nexec)*pow(10,6);
        removeL  /= (nexec)*pow(10,6);
        removeR  /= (nexec*ntries)*pow(10,6);
        gett     /= (nexec*ntries)*pow(10,6);
        myFile<<size<<","<<addF<<","<<addL<<","<<addR<<","<<removeF<<","<<removeL<<","<<removeR<<","<<gett<<endl;
        
        if (row % 10 == 0){
            cout << "[" << setw(2) << row << "/" << setw(3) << size << "]"
                 << ":\t"
                 << ptr_sizes[row] << "\t->"
                 << fixed << setw(12) << setprecision(4) << addF << ", "
                 << fixed << setw(12) << setprecision(4) << addL << ", "
                 << fixed << setw(12) << setprecision(4) << addR << ", "
                 << fixed << setw(12) << setprecision(4) << removeF << ", "
                 << fixed << setw(12) << setprecision(4) << removeL << ", "
                 << fixed << setw(12) << setprecision(4) << removeR << ", "
                 << fixed << setw(12) << setprecision(4) << gett << endl;
        }
        row++;
        SIZEth++;      
      }
      
      myFile.close();
}

/////////////////////////////////////////////////////////////////////////////
// YOUR ARE NOT REQUIRED TO CHANGE THE FOLLOWING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////

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
        meter2(&alist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if (option_exist(argv, argv + argc, "-s"))
    {
        cout << endl;
        cout << "SLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv + argc, "-s", "");
        meter2(&slist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if (option_exist(argv, argv + argc, "-d"))
    {
        cout << endl;
        cout << "DLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv + argc, "-d", "");
        meter2(&dlist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
}




// #include <iostream>
// #include <fstream>
// #include <chrono>
// #include <math.h>

// using namespace std;
// using namespace std::chrono;

// #include "list/XArrayList.h"
// #include "list/SLinkedList.h"
// #include "list/DLinkedList.h"
// #include "list/IList.h"
// #include "util/ArrayLib.h"
// #include <algorithm>
// #include <iomanip>


/*
NOTE:
  * SHOULD define other functions to support the implementation of "meter"
  * Parameters: read the explanation presented above
*/

