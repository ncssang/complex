#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <cmath>
#include <iostream>
#include <vector>

struct Complex
{
    float x;
    float y;

public:
    Complex(float x = 0, float y = 0);
    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;

    static Complex get_rotation_point(const Complex& source_point, const Complex& rotation);
    static Complex get_shear(const Complex& source_point, float scale);
    static Complex get_scaling(const Complex& source_point, const Complex& scale);
    static Complex get_reflection_point(const Complex& source_point);
    static Complex get_translation_point(const Complex& source_point, const Complex& translation);
};

#endif //COMPLEX_HPP
