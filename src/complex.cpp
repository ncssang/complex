#include "complex/complex.hpp"

Complex::Complex(float x, float y)
    : x(x), y(y)
{
}

Complex Complex::operator+(const Complex& c) const
{
    Complex complex;
    complex.x = this->x + c.x;
    complex.y = this->y + c.y;
    return complex;
}

Complex Complex::operator-(const Complex& c) const
{
    Complex complex;
    complex.x = this->x - c.x;
    complex.y = this->y - c.y;
    return complex;
}

Complex Complex::operator*(const Complex& c) const
{
    Complex complex;
    complex.x = this->x * c.x - this->y * c.y;
    complex.y = this->x * c.y + c.x * this->y;
    return complex;
}
