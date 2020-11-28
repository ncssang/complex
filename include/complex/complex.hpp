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
    Complex operator+(const Complex& c);
    Complex operator-(const Complex& c);
    Complex operator*(const Complex& c);
};

#endif //COMPLEX_HPP