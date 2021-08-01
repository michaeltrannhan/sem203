/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector3D.cpp
 * Author: LTSACH
 * 
 * Created on 8 June 2021, 18:43
 */

#include "geom/Vector3D.h"

ostream &operator<<( ostream &os, const Vector3D& vector){
    os << "V(" << fixed 
            << setw(6) << setprecision(2) << vector.x << "," 
            << setw(6) << setprecision(2) << vector.y << ","
            << setw(6) << setprecision(2) << vector.z
       << ")";
    return os;
}
Vector3D operator+(float s, const Vector3D& vector){
    return Vector3D(s+vector.x, s+vector.y, s+vector.z);
}
Vector3D operator-(float s, const Vector3D& vector){
    return Vector3D(s-vector.x, s-vector.y, s-vector.z);
}
Vector3D operator*(float s, const Vector3D& vector){
    return Vector3D(s*vector.x, s*vector.y, s*vector.z);
}
Vector3D operator/(float s, const Vector3D& vector){
    return Vector3D(s/vector.x, s/vector.y, s/vector.z);
}



Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const Vector3D& point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

Vector3D::~Vector3D() {
}

void Vector3D::setX(float x){
    this->x = x;
}
float Vector3D::getX() const{
    return this->x;
}
void Vector3D::setY(float x){
    this->y = y;
}
float Vector3D::getY() const{
    return this->y;
}
void Vector3D::setZ(float x){
    this->z = z;
}
float Vector3D::getZ() const{
    return this->z;
}

bool Vector3D::operator==(Vector3D rhs){
    return  (abs(this->x - rhs.x) < EPSILON) &&
            (abs(this->y - rhs.y) < EPSILON) &&
            (abs(this->z - rhs.z) < EPSILON);
}
Vector3D Vector3D::operator+(Vector3D other){
    return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}
Vector3D Vector3D::operator-(Vector3D other){
    return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}
Vector3D Vector3D::operator-(){
    return Vector3D(-this->x, -this->y, -this->z);
}
float Vector3D::operator*(Vector3D other){
    return this->x*other.x + this->y*other.y + this->z*other.z;
}
Vector3D Vector3D::operator*(float s){
    return Vector3D(this->x*s + this->y*s + this->z*s);
}
Vector3D::operator float(){
    return this->length();
}

void Vector3D::println(){
    cout << *this << endl;
}

float Vector3D::length(){
    float l2 = this->x*this->x + this->y*this->y + this->z*this->z;
    return sqrt(l2);
}
Vector3D& Vector3D::normalize(){
    float L = this->length();
    this->x /= L;
    this->y /= L;
    this->z /= L;
    return *this;
}
float Vector3D::angle(Vector3D& other){
    float DOT = *this * other;
    float La = this->length();
    float Lb = other.length();
    return acos(DOT/(La*Lb))*180/M_PI; //M_PI in math.h
}

/*
 a: this
 b: other
 -------CROSS = DETERMINANT --------
 i    j     k
 a.x  a.y   a.z
 b.x  b.y   b.z
 */
Vector3D Vector3D::cross(Vector3D& other){
    return Vector3D(
            this->y * other.z - other.y * this->z,
            -(this->x * other.z - other.x * this->z),
            this->x * other.y - other.x * this->y
            );
}


bool Vector3D::equals(Vector3D& lhs, Vector3D& rhs){
    return  lhs == rhs;
}

bool Vector3D::equals(Vector3D*& lhs, Vector3D*& rhs){
    return  *lhs == *rhs;
}

string Vector3D::toString(Vector3D& point){
    stringstream os;
    os  << point;
    return os.str();
}
string Vector3D::toString(Vector3D*& point){
    return toString(*point);
}

Vector3D* Vector3D::genVectors(int size, float minValue, float maxValue, 
                            bool manualSeed, int seedValue){
    Vector3D* head = new Vector3D[size];
        
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
        head[idx] = Vector3D(x,y,z);
    }
    delete engine;
    return head;
}