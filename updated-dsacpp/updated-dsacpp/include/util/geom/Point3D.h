/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point3D.h
 * Author: LTSACH
 *
 * Created on 8 June 2021, 18:42
 */

#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>
using namespace std;

#define EPSILON (1E-8)

#include "geom/Vector3D.h"
class Point3D {
public:
    friend ostream &operator<<( ostream &os, const Point3D& point);
    
    Point3D(float x=0.0f, float y=0.0f, float z=0.0f);
    Point3D(const Point3D& point);
    virtual ~Point3D();
    
    //Setter and Getter
    void setX(float z);
    float getX() const;
    void setY(float z);
    float getY() const;
    void setZ(float z);
    float getZ() const;
    
    //
    bool operator==(Point3D rhs);
    Vector3D operator-(Point3D other);
    Point3D operator+(Vector3D dir);
    operator float(); //cast a point to a float value
    
    
    float radius();
    void println();
    
    //static section  
    static bool equals(Point3D& lhs, Point3D& rhs); //with pointer to point
    static bool equals(Point3D*& lhs, Point3D*& rhs); //with pointer to point
    static string toString(Point3D& point);
    static string toString(Point3D*& point);
    
    
    // The the two following: generate and print an array of Point3D
    static Point3D* genPoints(  int size, 
                                float minValue=0, float maxValue=1, 
                                bool manualSeed=false, int seedValue=0);
    static Point3D* genPointsNormal(  int size, 
                                float *mu, //array 3 items
                                float *sigma, //array 3 items
                                bool manualSeed=false, int seedValue=0);
    static void println(Point3D* head, int size);
    
    
private:
    float x, y, z;   
};

#endif /* POINT3D_H */

