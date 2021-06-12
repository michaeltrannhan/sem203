/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point3D.cpp
 * Author: LTSACH
 * 
 * Created on 8 June 2021, 18:42
 */

#include "geom/Point3D.h"
#include "geom/Vector3D.h"

ostream &operator<<( ostream &os, const Point3D& point){
    os << "P(" << fixed 
            << setw(6) << setprecision(2) << point.x << "," 
            << setw(6) << setprecision(2) << point.y << ","
            << setw(6) << setprecision(2) << point.z
       << ")";
    return os;
}


Point3D::Point3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D::Point3D(const Point3D& point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

Point3D::~Point3D() {
}

void Point3D::setX(float x){
    this->x = x;
}
float Point3D::getX() const{
    return this->x;
}
void Point3D::setY(float x){
    this->y = y;
}
float Point3D::getY() const{
    return this->y;
}
void Point3D::setZ(float x){
    this->z = z;
}
float Point3D::getZ() const{
    return this->z;
}


bool Point3D::operator==(Point3D rhs){
    return  (abs(this->x - rhs.x) < EPSILON) &&
            (abs(this->y - rhs.y) < EPSILON) &&
            (abs(this->z - rhs.z) < EPSILON);
}

Vector3D Point3D::operator-(Point3D other){
    return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}
Point3D Point3D::operator+(Vector3D dir){
    return Point3D(this->x + dir.getX(), this->y + dir.getY(), this->z + dir.getZ());
}

Point3D::operator float(){
    return this->radius();
}

float Point3D::radius(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
void Point3D::println(){
    cout << *this << endl;
}


bool Point3D::equals(Point3D& lhs, Point3D& rhs){
    return  lhs == rhs;
}

bool Point3D::equals(Point3D*& lhs, Point3D*& rhs){
    return  *lhs == *rhs;
}

string Point3D::toString(Point3D& point){
    stringstream os;
    os  << point;
    return os.str();
}
string Point3D::toString(Point3D*& point){
    return toString(*point);
}

Point3D* Point3D::genPoints(int size, float minValue, float maxValue, 
                            bool manualSeed, int seedValue){
    Point3D* head = new Point3D[size];
        
    std::default_random_engine* engine;
    if(manualSeed)
        engine = new std::default_random_engine(static_cast<long unsigned int>(seedValue));
    else
        engine = new std::default_random_engine(static_cast<long unsigned int>(time(0)));
    uniform_real_distribution<double> dist(minValue, maxValue);

    //
    for(int idx=0; idx < size; idx++){
        float x = dist(*engine);
        float y = dist(*engine);
        float z = dist(*engine);
        head[idx] = Point3D(x,y,z);
    }
    delete engine;
    return head;
}

void Point3D::println(Point3D* head, int size){
    stringstream os;
    os << "[\n";
    for(int idx=0; idx < size; idx++) os << head[idx] << endl;
    os << "]\n";
    cout << os.str() << endl;
    return;
}

