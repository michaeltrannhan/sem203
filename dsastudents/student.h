#ifndef student_h
#define student_h
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
    string sub_strname = sname.substr(lengthname - NITEMS/2 - 1, NITEMS/2);
    string sub_strcode = scode.substr(lengthcode - NITEMS/2 - 1, NITEMS/2);
    string total_sub = sub_strname + sub_strcode;
    for (int i = 0; i < NITEMS; i++){
        student_data[i] = (int)(total_sub[i]);
    }
}

#endif