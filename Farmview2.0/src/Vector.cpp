#include "Vector.h"

// Start vectors x and y at 0:
Vector::Vector()
{
    x = 0.0f;
    y = 0.0f;
}


// Vector floats:
Vector::Vector(float x, float y)
{
    // When local variable’s name is same as member’s name we use 
    // "this" pointer to reference the member's name:
    this->x = x;
    this->y = y;
}

// Vector arithmetic:
Vector& Vector::Add(const Vector& vector)
{
    this->x += vector.x;
    this->y += vector.y;

    return *this;
}

Vector& Vector::Subtract(const Vector& vector)
{
    this->x -= vector.x;
    this->y -= vector.y;

    return *this;
}

Vector& Vector::Multiply(const Vector& vector)
{
    this->x *= vector.x;
    this->y *= vector.y;

    return *this;
}

Vector& Vector::Divide(const Vector& vector)
{
    this->x /= vector.x;
    this->y /= vector.y;

    return *this;
}


// Vector operators:
Vector& operator+(Vector& vector1, const Vector& vector2)
{
    // When returning reference to the calling object we use 
    // "this" pointer -- When a reference to a local object is returned, 
    // the returned reference can be used to chain function calls on a single object.
    return vector1.Add(vector2);
}

Vector& operator-(Vector& vector1, const Vector& vector2)
{
    return vector1.Subtract(vector2);
}

Vector& operator*(Vector& vector1, const Vector& vector2)
{
    return vector1.Multiply(vector2);
}

Vector& operator/(Vector& vector1, const Vector& vector2)
{
    return vector1.Divide(vector2);
}


// Vector stacked operators:
Vector& Vector::operator+=(const Vector& vector)
{
    return this->Add(vector);
}

Vector& Vector::operator-=(const Vector& vector)
{
    return this->Subtract(vector);
}

Vector& Vector::operator*=(const Vector& vector)
{
    return this->Multiply(vector);
}

Vector& Vector::operator/=(const Vector& vector)
{
    return this->Divide(vector);
}


Vector& Vector::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

Vector& Vector::Zero()
{
    this->x *= 0;
    this->y *= 0;

    return *this;
}


std::ostream& operator << (std::ostream& stream, const Vector& vector)
{
    stream << "Vector: (" << vector.x << ", " << vector.y << ")";
    return stream;
}