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
};

#endif //COMPLEX_HPP