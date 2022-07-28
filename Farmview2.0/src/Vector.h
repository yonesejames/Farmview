#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>

class Vector
/*
    A vector is an object that has both a magnitude and a direction. 
    Geometrically, we can picture a vector as a directed line segment, 
    whose length is the magnitude of the vector and with an arrow indicating 
    the direction. The direction of the vector is from its tail to its head.
*/
{
public:
    float x;
    float y;

    Vector();
    Vector(float x, float y);

    Vector& Add(const Vector& vector);
    Vector& Subtract(const Vector& vector);
    Vector& Multiply(const Vector& vector);
    Vector& Divide(const Vector& vector);
   
    // "friend" declaration grants a function or another class access to private and 
    // protected members of the class where the friend declaration appears:
    friend Vector& operator+(Vector& vector1, const Vector& vector2);
    friend Vector& operator-(Vector& vector1, const Vector& vector2);
    friend Vector& operator*(Vector& vector1, const Vector& vector2);
    friend Vector& operator/(Vector& vector1, const Vector& vector2);

    Vector& operator+=(const Vector& vector);
    Vector& operator-=(const Vector& vector);
    Vector& operator*=(const Vector& vector);
    Vector& operator/=(const Vector& vector);

    Vector& operator*(const int& i);
    Vector& Zero();

    friend std::ostream& operator << (std::ostream& stream, const Vector& vector);
    
};


#endif VECTOR_H

