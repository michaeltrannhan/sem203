#include <iostream>
//#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
#include "util/FileIOLib.h"
using namespace cv;
using namespace std;

typedef unsigned char uint8;
typedef unsigned int  uint32;


template<class T>
class ISortEx{
public:
    virtual ~ISortEx(){};
    virtual void sort(T array[], int size, int (*comparator)(T&,T&) =0, int stride=1) = 0;
};

template<class T>
class SortSimpleOrderEx{
public:
    static int compare4Ascending(T& lhs, T& rhs){
        if(lhs < rhs) return -1;
        else if(lhs > rhs) return +1;
        else return 0;
    }
    static int compare4Desending(T& lhs, T& rhs){
        if(lhs < rhs) return +1;
        else if(lhs > rhs) return -1;
        else return 0;
    }
};

template<class T>
class StraightSelectionSortEx: public ISortEx<T>{
public:   
    void sort(T array[], int size, int (*comparator)(T&,T&)=0, int stride=1){
        int current, smallest, walker;
        
        current = 0; 
        while(current < stride*(size - 1)){
            //removed
            walker = current + stride;
            while(walker < size*stride){
                //removed
                if(comparator(array[walker], array[smallest])<0){
                    smallest = walker;
                }
                walker += stride;
            }
            if(smallest != current){
                //swap:
                T temp= array[smallest];
                array[smallest] = array[current];
                array[current]= temp;
                //removed
            }
            current += stride;
        }
    }

};
/////////////////////////////////////////////////////////////////////////////////////////
// Command line parsing functions
/////////////////////////////////////////////////////////////////////////////////////////

int get_int(char** begin, char** end, const string& option, int _default){
    char** ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end) return stoi(*ptr);
    else return _default;
}

string get_string(char** begin, char** end, const string& option, string _default){
    char** ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end) return string(*ptr);
    else return _default;
}
bool option_exist(char** begin, char** end, const string& option){
    return std::find(begin, end, option) != end;
}
string trimstring(string str) {
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0,str.find_first_not_of(typeOfWhitespaces));
    return str;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Command line parsing functions: END
/////////////////////////////////////////////////////////////////////////////////////////

void sort_file(string file, string input, string output, bool inrow=true){
    string inputfile = input + "/" + file;
    string outputfile = output + "/" + file;
    cv::Mat image = cv::imread(inputfile, cv::IMREAD_GRAYSCALE);

    if (image.empty()) cout << inputfile << ": not found!" << endl;
    
    //Here: valid image:
    cout << "filename: " << inputfile << endl;
    cout << "(nrows, ncols, nchannels) = " 
        << "("  << image.rows << ", "
                << image.cols << ", "
                << image.channels()
        << ")" << endl;
    cout << "number of pixels: " << image.rows* image.cols * image.channels() << endl;
    cout << endl;

    ISortEx<uint8>* sorter = new StraightSelectionSortEx<uint8>();
    if(inrow){
        //sort data in rows
        for(int r=0; r < image.rows; r++){
            //removed
            uint8 *head = image.ptr<uint8>(r, 0);
            int stride = 1;
            int nitems = image.cols;
            sorter->sort(head, nitems,  &SortSimpleOrderEx<uint8>::compare4Ascending, 1);
        }
        outputfile = output + "/" + file.substr(0, file.rfind('.')) + "_rows.png";
    }
    else{
        //sort data in columns
        for(int c=0; c < image.cols; c++){
            //removed
            uint8 *head = image.ptr<uint8>(c, 0);
            int stride = image.step;
            int nitems = image.cols;
            sorter->sort(head, nitems,  &SortSimpleOrderEx<uint8>::compare4Ascending, stride);
        }
        outputfile = output + "/" + file.substr(0, file.rfind('.')) + "_cols.png";
    }
    cv::imwrite(outputfile, image); //write image file with extension PNG

    delete sorter;
}
/*
10, 21, 5,  127,
5,  18, 17, 20,
25, 35, 40, 50

nrows: 3
ncols: 4
*/

int main(int argc, char** argv){
    if(option_exist(argv, argv+argc, "-h")){
        cout << "Show help" << endl;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////////
    string input = get_string(argv, argv+argc, "-in", "input");
    string output = get_string(argv, argv+argc, "-out", "output");
    string filelist = get_string(argv, argv+argc, "-list", "filelist.csv");
    
    DataFrame master(input + "/" + filelist);
    vector<string> filenames = master["filename"];
    vector<string> outfiles;
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        sort_file(trimstring(filename), input, output, true);
        sort_file(trimstring(filename), input, output, false);
        outfiles.push_back(filename);
    }

    DataFrame outmaster;
    outmaster.add("filename", outfiles);
    outmaster.write(output + "/" + filelist);
    return 0;
}