/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector3D.h
 * Author: LTSACH
 *
 * Created on 8 June 2021, 18:43
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>
using namespace std;

#define EPSILON (1E-8)

class Vector3D {
public:
    friend ostream &operator<<( ostream &os, const Vector3D& vector);
    friend Vector3D operator+(float s, const Vector3D& vector);
    friend Vector3D operator-(float s, const Vector3D& vector);
    friend Vector3D operator*(float s, const Vector3D& vector);
    friend Vector3D operator/(float s, const Vector3D& vector);
    
    Vector3D(float x=0.0f, float y=0.0f, float z=0.0f);
    Vector3D(const Vector3D& vector);
    virtual ~Vector3D();
    
    //Setter and Getter
    void setX(float z);
    float getX() const;
    void setY(float z);
    float getY() const;
    void setZ(float z);
    float getZ() const;
    
    //
    bool operator==(Vector3D rhs);
    Vector3D operator+(Vector3D other);
    Vector3D operator-(Vector3D other);
    Vector3D operator-();
    float operator*(Vector3D other); //dot-product
    Vector3D operator*(float s); //scaling with a factor
    operator float(); //cast a vector to a float value
    
    //
    void println();
    float length();
    Vector3D& normalize();
    float angle(Vector3D& other); //in degree
    Vector3D cross(Vector3D& other); //cross-product
    
    
    //Static section
    static bool equals(Vector3D& lhs, Vector3D& rhs); //with pointer to point
    static bool equals(Vector3D*& lhs, Vector3D*& rhs); //with pointer to point
    static string toString(Vector3D& point);
    static string toString(Vector3D*& point);
    
private:
    float x, y, z;   
};

#endif /* VECTOR3D_H */

