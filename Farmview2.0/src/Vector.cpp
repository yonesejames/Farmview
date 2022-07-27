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