#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <chrono>
#include <tree/AVL.h>
#include <tree/BST.h>
#include <tree/IBST.h>
#include <list/DLinkedList.h>
#include <list/IList.h>
#include <list/SLinkedList.h>
#include <list/XArrayList.h>
#include <util/ArrayLib.h>
#include <util/Point.h>
#include <geom/Vector3D.h>
#include <geom/Point3D.h>


/**
 * @brief 
 * 
Part II: Qualitatively Grading, by picture (20%)
HOW TO:
* Create pictures show comparisons for the execution time for following methods:
   (1) Figure-1: comparison:  add(k, item) in List (XArrayList, SLinkedList, DLinkedList) vs add(key=item, value=item) in BST, AVL
           >> item: int, Vector3D
           >> Number of items shoud be thousands instead of millions to be workable for BST
   (2) Searching time for Lists and BST, AVL:
       (2.1) develop one search function receiving a list (IList*) and item:
                * action: search
                * return: pointer to the item if found ELSE return NULL
        (2.2) create a figure compares the times of (2.1) and search method in BST/AVL
 * 
 */
using namespace std;
using namespace std::chrono;

template<class T>
double add_SLL(T &list, int randVal, int  nexec){
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(randVal, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}


template<class T>
double add_SLL(T &list, int randVal, int  nexec){
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(randVal, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}

template<class T>
double add_DLL(T &list, int randVal, int  nexec){
    double total = 0;
    for (auto size = 0; size < nexec ; size++)
    {
        auto start = chrono::high_resolution_clock::now();
        list->add(randVal, 10);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        total += duration;
    }
    return total;
}


template<class K, class V>
double add_BST(int randVal, int nexec){
    double total = 0;
    for(auto size = 0; size < nexec; size++){
        auto start = chrono::high_resolution_clock::now();
        tree->add(randVal, randVal*2);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        total+=duration;
    }
    return total;
}



template<class T>
void meter(T* list, string csvfile, int  *ptr_sizes, int nsizes, int nexec = 10, int ntries = 10){
    fstream fout;
    fout.open(csvfile);
    fout << "size"
         << ","
         << "add(k, item)(ms)"
        //  << ","
        //  << "add(k, item)VECTOR(ms)" 
        //  << ","
        //  << "add(k, item)SLL(ms)"
        //  << ","
        //  << "add(k, item)DLL(ms)"
        //  << ","
        //  << "add(key, value)BST(ms)"
        //  << ","
        //  << "add(key, value)AVL(ms)"
         << endl;
    cout << "idx/size"
         << ":\t"
         << "n"
         << ":\t"
         << fixed << setw(15) << setprecision(4) << "add(k, item)(ms)"
        //  << ", "
        //  << fixed << setw(15) << setprecision(4) << "add(k, item)vec(ms)"
        //  << fixed << setw(15) << setprecision(4) << "add(k, item)SLL(ms)"
        //  << ", "
        //  << fixed << setw(15) << setprecision(4) << "add(k, item)DLL(ms)"
        //  << ", "
        //  << fixed << setw(15) << setprecision(4) << "add(k, item)BST(ms)"
        //  << ", "
        //  << fixed << setw(15) << setprecision(4) << "add(k, item)AVL(ms)"
         << endl;
    for (int i = 0; i < nsizes; i++)
    {
        list->clear();
        for (int j = 0; j < ptr_sizes[i]; j++)
        {
            list->add(j);
        }
        
        int size = ptr_sizes[i];
     
        double addrand = add(plist, nexec) / (nexec);
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
    BST<int, int*> bst;
    AVL<int, int*> avl;


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
    if (option_exist(argv, argv + argc, "-s"))
    {
        cout << endl;
        cout << "BST: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv + argc, "-bst", "");
        meter(&bst, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if (option_exist(argv, argv + argc, "-s"))
    {
        cout << endl;
        cout << "AVL: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv + argc, "-avl", "");
        meter(&avl, filename, ptr_sizes, nsizes, nexec, ntries);
    }
}