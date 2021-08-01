#include <iostream>
#include <iomanip>
#include "list/XArrayList.h"
#include "util/FileIOLib.h"
#include "geom/Point3D.h"
#include "geom/Vector3D.h"
#include "list/DLinkedList.h"
using namespace std;

/* 2 points */
XArrayList<Point3D> make_grid(float xmin, float xmax, float ymin, float ymax, int nitems=100){
    //YOUR CODE HERE
    float DELTAX = (xmax-xmin)/nitems;
    float DELTAY = (ymax-ymin)/nitems;

    XArrayList<Point3D> results;
    for(int i = 0;i<nitems; i++){
        float current_x = xmin+DELTAX*i;
        for(int j = 0; j< nitems; j++){
            float current_y = ymin+DELTAY*j;
            results.add(Point3D(current_x, current_y,0));
        }
    }
    return results;
}

/* 1 points */
XArrayList<Point3D> make_parabol(XArrayList<Point3D> xy){
    //YOUR CODE HERE
    float x=0, y=0, z =0;
    XArrayList<Point3D> list = xy;
    XArrayList<Point3D> temp;
    for(int i = 0; i < xy.size(); i++){
        x = list.get(i).getX();
        y = list.get(i).getY();
        z = x*x+y*y;
        temp.add(Point3D(x, y, z));
    }
   return temp;
}

/* 2 points */
void bbox(XArrayList<Point3D>& points, Point3D& lt, Point3D& rb){
    //YOUR CODE HERE
    float largest_x=0, largest_y=0, smallest_x=INT8_MAX, smallest_y=INT8_MAX;
    for(int i=0; i< points.size(); i++){
        if(largest_x < points.get(i).getX()) largest_x = points.get(i).getX();
        if(largest_y < points.get(i).getX()) largest_y = points.get(i).getX();
        if(smallest_x > points.get(i).getX()) smallest_x = points.get(i).getX();
        if(smallest_y > points.get(i).getX()) smallest_y = points.get(i).getX();
    }

    for(int i =0 ; i<points.size();i++){
        if(points.get(i).getX() == smallest_x && points.get(i).getY()== smallest_y)
            lt = points.get(i);
        if(points.get(i).getX() == largest_x && points.get(i).getY()== largest_y)
            rb = points.get(i);
    }
    return;
    
}


/////////////////////////////////////////////////////////////////////////////////
// DO NOT CHANGE THE CODE FOLLOWING
/////////////////////////////////////////////////////////////////////////////////

XArrayList<Point3D> gen_points(int size = 100){
    XArrayList<Point3D> points;
    //Point3D *ptr = Point3D::genPoints(size, 5, 20, true, 2021);
    float mu[] = {2.0f, 2.0f, 0.0f};
    float sigma[] = {2.0f, 1.0f, 0.0f};
    Point3D *ptr = Point3D::genPointsNormal(size, mu, sigma, true, 2021);
    for(int idx=0; idx < size; idx++) points.add(ptr[idx]);

    delete []ptr;
    return points;
}

void store_bb(XArrayList<Point3D> points, string filename){
    Point3D lt, rb;
    bbox(points, lt, rb);
    //
    vector<string> x_vec, y_vec;
    XArrayList<Point3D>::Iterator it;
    for(it=points.begin(); it != points.end(); it++){
        Point3D point = *it;
        stringstream xos, yos;
        xos << fixed << setw(8) << setprecision(4) << point.getX();
        yos << fixed << setw(8) << setprecision(4) << point.getY();
        x_vec.push_back(xos.str());
        y_vec.push_back(yos.str());
    }
    
    vector<string> ltx_vec, lty_vec, rbx_vec, rby_vec;
    stringstream ltxos, ltyos, rbxos, rbyos;
    ltxos  << fixed << setw(8) << setprecision(4) << lt.getX();
    ltyos  << fixed << setw(8) << setprecision(4) << lt.getY();
    rbxos  << fixed << setw(8) << setprecision(4) << rb.getX();
    rbyos  << fixed << setw(8) << setprecision(4) << rb.getY();
    ltx_vec.push_back(ltxos.str());
    lty_vec.push_back(ltyos.str());
    rbx_vec.push_back(rbxos.str());
    rby_vec.push_back(rbyos.str());
    DataFrame df;
    df.add("x", x_vec);
    df.add("y", y_vec);
    df.add("lt.x", ltx_vec);
    df.add("lt.y", lty_vec);
    df.add("rb.x", rbx_vec);
    df.add("rb.y", rby_vec);
    
    df.write(filename, ';');
}

void store_points(XArrayList<Point3D> points, string filename){
    vector<string> x_vec, y_vec, z_vec;
    XArrayList<Point3D>::Iterator it;
    for(it=points.begin(); it != points.end(); it++){
        Point3D point = *it;
        stringstream xos, yos, zos;
        xos << fixed << setw(8) << setprecision(4) << point.getX();
        yos << fixed << setw(8) << setprecision(4) << point.getY();
        zos << fixed << setw(8) << setprecision(4) << point.getZ();
        x_vec.push_back(xos.str());
        y_vec.push_back(yos.str());
        z_vec.push_back(zos.str());
    }
    DataFrame df;
    df.add("x", x_vec);
    df.add("y", y_vec);
    df.add("z", z_vec);
    df.write(filename);
}

int main(int argc, char **argv){
    XArrayList<Point3D> grid = make_grid(-5, 5, -5, 5, 10);
    XArrayList<Point3D> grid2 = make_grid(-5, 5, -5, 5, 100);
    XArrayList<Point3D> parabol = make_parabol(grid2);

    // XArrayList<Point3D> points = gen_points(200);

    store_points(grid, "grid.csv");
    store_points(parabol, "parabol.csv");
    // store_bb(points, "bbox.csv");

    return 0;
}