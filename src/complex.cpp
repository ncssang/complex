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

Complex Complex::get_rotation_point(const Complex& source_point, const Complex& rotation)
{
    Complex destination_point;
    destination_point = source_point * rotation;
    return destination_point;
}

Complex Complex::get_shear(const Complex& source_point, float scale)
{
    Complex destination_point;
    destination_point.x = source_point.x + source_point.y * scale;
    destination_point.y = source_point.y;
    return destination_point;
}

Complex Complex::get_scaling(const Complex& source_point, const Complex& scale)
{
    Complex destination_point;
    destination_point.x = source_point.x * scale.x;
    destination_point.y = source_point.y * scale.y;
    return destination_point;
}

Complex Complex::get_reflection_point(const Complex& source_point)
{
    Complex destination_point;
    destination_point.x = -source_point.x;
    destination_point.y = source_point.y;
    return destination_point;
}

Complex Complex::get_translation_point(const Complex& source_point, const Complex& translation)
{
    Complex translation_point;
    translation_point = source_point + translation;
    return translation_point;
}
