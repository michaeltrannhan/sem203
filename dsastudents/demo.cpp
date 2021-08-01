#include <iostream>
#include "graph/AbstractGraph.h"
#include "graph/DGraphModel.h"
#include "graph/DGraphDemo.h"
#include "graph/IGraph.h"
#include "graph/UGraphDemo.h"
#include "graph/UGraphModel.h"
#include "graph/TopoSorter.h"

#include <string>
#define NITEMS 10
using namespace std;

string sname = "TRANNGUYENPHUOCNHAN"; //Fill your name here without sapces
string scode = "1952893"; //Fill your student id here

/////////////////////////////////////////////////////////////////////////
int student_data[NITEMS];

/*point: 0.5*/
void gen_student_data(){
    //YOUR CODE HERE
    int lengthname = sname.length();
    int lengthcode = 7;
    string sub_strname = sname.substr(lengthname - NITEMS/2 , NITEMS/2);
    string sub_strcode = scode.substr(lengthcode - NITEMS/2 , NITEMS/2);
    string total_sub = sub_strname + sub_strcode;
    for (int i = 0; i < NITEMS; i++){
        student_data[i] = (int)(total_sub[i]);
    }
}
using namespace std;

int main(){
    // DGraphDemo2();
    gen_student_data();
    for(int i = 0; i < NITEMS ; i++){
        cout << student_data[i] << endl;
    }
}