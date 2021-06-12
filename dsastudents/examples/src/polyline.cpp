#include <iostream>
#include <iomanip>
#include "list/XArrayList.h"
#include "geom/Point3D.h"
#include "geom/Vector3D.h"
using namespace std;

float length_by_index(XArrayList<Point3D*> &list){
    float length = 0;
    for(int idx=1; idx < list.size(); idx++){
        Point3D* prev = list.get(idx - 1);
        Point3D* cur = list.get(idx);
        Vector3D v = *cur - *prev;
        length += v.length();
    }
    return length;
}
float length_by_iterator(XArrayList<Point3D*> &list){
    float length = 0;
    if(list.size() < 2) return length;

    XArrayList<Point3D*>::Iterator it = list.begin();
    Point3D* prev = *it;
    for(/*no actions*/; it != list.end(); it++){
        Point3D* cur = *it;
        Vector3D v = *cur - *prev;
        length += v.length();

        prev = cur;
    }
    return length;
}

int main(int argc, char** argv) {
    //Preparing data
    int nPoints = 5; //change to the number wanted
    Point3D*  points = Point3D::genPoints(nPoints, -10.0f, +10.0f);

    XArrayList<Point3D*> list; // !!!!list of pointers!!!!
    for(int idx=0; idx < nPoints; idx++) list.add(&points[idx]);

    //Here, "list" contains a sequence of points (containing pointers instead of Point3D objects)
    list.println(Point3D::toString);

    //Compute the polyline's length
    float L_by_index = length_by_index(list);
    float L_by_iterator = length_by_iterator(list);
    cout << "Polyline's length: " << fixed << setw(6) << setprecision(2) << L_by_index << endl;
    cout << "Polyline's length: " << fixed << setw(6) << setprecision(2) << L_by_iterator << endl;

    //Free memory and return
    delete []points;
    return 0;
}

 