#include <iostream>
#include <iomanip>

#include "geom/Point3D.h"
#include "geom/Vector3D.h"
using namespace std;

int main(int argc, char** argv) {
    Point3D A = Point3D(0, 0, 0);
    Point3D B = Point3D(2, 0, 0);
    Point3D C = Point3D(0, 2, 0);

    cout << "The vertices of the triangle:" << endl;
    A.println(); B.println(); C.println();

    Vector3D AB = B - A;
    Vector3D AC = C - A;
    Vector3D cross = AB.cross(AC);
    float sABC = 0.5 * cross.length();
    cout << "sABC = " << fixed << setw(6) << setprecision(2) << sABC << endl;

    return 0;
}

 