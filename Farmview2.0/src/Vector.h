#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
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

