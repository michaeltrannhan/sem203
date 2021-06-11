#include <iostream>
#include <iomanip>
#include "dsacpp/include/util/Point.h"
#include "dsacpp/include/geom/Vector3D.h"

using namespace std;

int main(int argc, char** argv)
{
    Vector3D v1(1.5, 2.5, 3.0);
    Vector3D v2(1.0, 0.0, 0.0);
    Vector3D v3 = v2 + v1;
    cout << v3 << endl;
}