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
    void print();
};

Complex::Complex(float x, float y)
    : x(x), y(y)
{
}

Complex Complex::operator+(const Complex& c)
{
    Complex complex;
    complex.x = this->x + c.x;
    complex.y = this->y + c.y;
    return complex;
}

Complex Complex::operator-(const Complex& c)
{
    Complex complex;
    complex.x = this->x - c.x;
    complex.y = this->y - c.y;
    return complex;
}

Complex Complex::operator*(const Complex& c)
{
    Complex complex;
    complex.x = this->x * c.x - this->y * c.y;
    complex.y = this->x * c.y + c.x * this->y;
    return complex;
}

void Complex::print()
{
    std::cout << "z = " << x << " + " << y << "*i" << std::endl;
}

int main()
{
    float cos = sin(M_PI / 6.0);
    std::cout << cos << std::endl;
    Complex complex_1(4, 3), complex_2(0, 1);
    complex_1.print();
    complex_2.print();
    Complex add = complex_1 + complex_2;
    add.print();
    Complex subtract = complex_1 - complex_2;
    subtract.print();
    Complex multiple = complex_1 * complex_2;
    multiple.print();
}