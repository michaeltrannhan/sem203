#include <iostream>
#include <iomanip>
#include "list/XArrayListDemo.h"
#include "util/Point.h"
#include "util/ArrayLib.h"
#include "list/XArrayList.h"
#include "geom/Point3D.h"
#include "sorting/XArrayListSE.h"


using namespace std;


int sortPointComparator(Point*& lhs, Point*& rhs){
    if(lhs->getX() < rhs->getX()) return -1;
    else if(lhs->getX() > rhs->getX()) return +1;
    else return 0;
}
int sortPointComparatorDESC_Y(Point*& lhs, Point*& rhs){
    if(lhs->getY() < rhs->getY()) return +1;
    else if(lhs->getY() > rhs->getY()) return -1;
    else return 0;
}
void listSortDemo3(){
    int size = 5;
    Point* items = Point::genPoints(size, -10, 10);
    XArrayListSE<Point*> list;
    for(int i=0; i < size; i++) list.add(&items[i]);
    
    list.println(&Point::point2str);
    
    cout << "Ascending:" << endl;
    list.sort(&sortPointComparator);
    list.println(&Point::point2str);
    
    cout << "Descending:" << endl;
    list.sort(&sortPointComparatorDESC_Y);
    list.println(&Point::point2str);
 
    //
    delete []items;
}

int main(int argc, char** argv) {
    //xlistDemo4();
    listSortDemo3();
    return 0;
}

