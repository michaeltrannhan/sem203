#include <iostream>
#include <iomanip>

#include "list/XArrayList.h"
#include "geom/Point3D.h"
using namespace std;

int main(int argc, char** argv) {
    cout << "1. Creating a simple array list" << endl;
    XArrayList<Point3D> list;

    cout << "2. Adding four points to the list" << endl;
    list.add(Point3D(1, 2, 3));
    list.add(Point3D(2, 3, 4));
    list.add(Point3D(4, 5, 6));
    list.add(Point3D(7, 8, 9));

    cout << "3. Displaying the list" << endl;
    list.println();

    return 0;
}

