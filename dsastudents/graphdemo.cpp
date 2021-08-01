#include "graph/DGraphModel.h"
#include "graph/TopoSorter.h"
#include "graph/IGraph.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
bool charComparator(char& lhs, char& rhs){
    return lhs==rhs;
}
string vertex2str(char& v){
    stringstream os;
    os << v;
    return os.str();
}
int main(){
    DGraphModel<char> graph(&charComparator, &vertex2str);
    char vertices[] = {'a', 'b', 'c', 'd'};
    for (char vertex : vertices){
        graph.add(vertex);
    }
    
}