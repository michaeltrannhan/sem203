#include <iostream>
#include <iomanip>
#include "util/ArrayLib.h"
#include "util/FuncLib.h"
#include "util/FileIOLib.h"
#include "geom/Vector3D.h"
#include "geom/Point3D.h"
#include "graph/DGraphModel.h"
#include "graph/TopoSorter.h"
using namespace std;
#include <math.h>
/*1 points*/

int hash_code(char& key, int size){
    return (int)key % size;
}
bool charComparator(string lhs, string rhs){
    return lhs==rhs;
}
string vertex2str(char& v){
    stringstream os;
    os << v;
    return os.str();
}
DGraphModel<string> *create_graph(){
    //YOUR CODE HERE to define and return the Graph
    DGraphModel<string> model(&charComparator, &vertex2str);
    string names[]={"Hash", "List","SortingAlgorithms", "StackQueue","Heap","Tree","Graph"};
    for(int idx = 0; idx<7; idx++){
        model.add(names[idx]);
    }
    model.connect("Graph", "Hash", 0);
    model.connect("Graph", "List", 0);
    model.connect("Graph", "StackQueue", 0);
    model.connect("List", "SortingAlgorithms", 0);
    model.connect("Tree", "List", 0);
    model.connect("Tree", "StackQueue", 0);
    model.connect("StackQueue", "Heap", 0);
    model.connect("StackQueue", "List", 0);
    model.connect("SortingAlgorithms", "Heap", 0);
    
    return model;
}

/*1 points*/
void compile_modules(DGraphModel<string> * graph, void (*compile)(string)){
    //YOUR CODE HERE to compile modules => call "compile" if you want to compile any module

   
}


///////////////////////////////////////////////////////////////////
///// DO NOT CHANGE THE FOLLOWING
///////////////////////////////////////////////////////////////////
void do_compilation(string module){
    module = "\"" + module + "\"";
    cout << "Compile " << setw(30) << left << module << "... Done!" << endl;
}
int main(int argc, char** argv){
    DGraphModel<string> *graph = create_graph();
    compile_modules(graph, &do_compilation);
    delete graph;
    return 0;
}
