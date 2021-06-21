/*  
2. How to timeit for list's operations
listimeit must do timeit for lists having different sizes. The size of the list is the horizontal axis of the figure.

The maximum length of lists in the figure is one milion; however, listimeit needs not to dertermine the executation time for every size from 1 to one milion.

listitimeit samples the size by uniform distribution within [1, max_length]; for example, if max_length is 10^6 then size is any random value within [1, 10^6]

one sample (one value of size) generates one row in CSV file.
the total number of rows in CSV file can be controlled by a value nsizes
max_length and nsizes can be passed as command line arguments for listimeit, as follows
./listtimeit -a filename.csv -nsizes 100 -max_length 1000000

With the command above:
nsizes = 10
max_length=10^6
CSV file is filename.csv
-a means: do timeit for XArrayList
meanwhile, -s for SLinkedList and -d for DLinkedList
for each size in nsizes, listimeit has to determine executation time for the afore-mentioned methods: add, remove, get.

to obtain reliable estimation for times, listtimeit has to run each methods nexec times and take the averaged value for nexec tries. nexec can be also controlled via command line arguments, as follows:
./listtimeit -a filename.csv -nsizes 100 -max_length 1000000 -nexec 20

The above command: nexec=20 means that listimeit run each method 20 times and compute the averaged execution time.
Moreover, methods like add(k,*), removeAt(k) and get(k); where, k is a valid index, within [0, size]. listtimeit SHOUD NOT fix k to a static value. It SHOULD do sampling to get k. That means k is sampled from a uniform distribution [0, size].

How many values of k should be sampled can be controlled by a value named ntries, via command line, for examples.
./listtimeit -a filename.csv -nsizes 100 -max_length 1000000 -nexec 20 -ntries 10

listtimeit will executes each method add(k,*), removeAt(k) and get(k) [nexec x ntries] and return the averaged time. Within the command here, [nexec x ntries] = 20x10 = 200 tries.
 */

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "dsacpp/include/list/IList.h"
#include "dsacpp/include/list/XArrayList.h"
#include "dsacpp/include/list/SLinkedList.h"
#include "dsacpp/include/list/DLinkedList.h"
#include "dsacpp/include/util/ArrayLib.h"
x
using namespace std;
using namespace std::chrono;
/*
!NOTE:
  * SHOULD define other functions to support the implementation of "meter"
  * Parameters: read the explanation presented above
*/

void meter(IList<int> *plist, string csvfile, int *ptr_sizes, int nsizes, int nexec = 10, int ntries = 10)
{
    //YOUR CODE HERE
    ofstream fout;
    fout.open(csvfile, ios::out | ios::app);
    fout << "size, addfirst(ms), addlast(ms), addrandpos(ms), removefirst(ms), removelast(ms), removerandpos(ms), getrandpos(ms)" << endl;
    //plist = new IList<int>[nsizes]();
    for (int i = 0; i < nsizes; i++)
    {
        for (int j = 0; j < ptr_sizes[i]; j++)
        {
            plist->add(j);
        }
        srand(time(0));
        double total1 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->add(0, 10);
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total1 += duration;
        }
        double total2 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->add(10);
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total2 += duration;
        }
        double total3 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->add((rand()%static_cast<int>(size)), 10);
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total3 += duration;
        }
        double total4 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->removeAt(0);
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total4 += duration;
        }
        double total5 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->removeAt((rand()%static_cast<int>(size)));
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total5 += duration;
        }
        double total6 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->removeAt((rand()%static_cast<int>(size)));
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total6 += duration;
        }
        double total7 = 0;
        for (auto size = 0; size < nexec * ntries; size++)
        {
            auto start = chrono::high_resolution_clock::now();
            //for(int i = 0; i < 626654; i++)
            plist->get((rand()%static_cast<int>(size)));
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            total7 += duration;
        }

        int size = ptr_sizes[i];
        double addfirst    = total1 / (nexec * ntries);
        double addlast     = total2 / (nexec * ntries);
        double addrand     = total3 / (nexec * ntries);
        double removefisrt = total4 / (nexec * ntries);
        double removelast  = total5 / (nexec * ntries);
        double removerand  = total6 / (nexec * ntries);
        double getrand     = total7 / (nexec * ntries);
        fout << size << "," << addfirst << "," << addlast << "," << addrand << "," << removefisrt << "," << removelast << "," << removerand << "," << getrand << endl;
    }
    fout << "\n";
    fout.close();
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

    cout << nsizes << ", " << nexec << ", " << max_length << ", " << ntries << endl;
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