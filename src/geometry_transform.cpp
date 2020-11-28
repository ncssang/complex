#include <cmath>
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <stdio.h>
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

int main()
{
    std::vector<Complex> points;
    Complex point;
    std::vector<int> numbers_x;
    std::vector<int> numbers_y;
    for (size_t i = 0; i < 10; ++i)
    {
        numbers_x.push_back(int(rand() % 250));
        numbers_y.push_back(int(rand() % 250));
    }
    for (size_t i = 0; i < numbers_x.size(); ++i)
    {
        point.x = numbers_x[i];
        point.y = numbers_y[i];
        points.push_back(point);
    }

    // std::vector<Complex> points_translation;
    // Complex translation;
    // translation.x = 0;
    // translation.y = 50;
    // for (size_t i = 0; i < points.size(); ++i)
    // {
    //     Complex complex;
    //     complex = points[i] + translation;
    //     points_translation.push_back(complex);
    // }

    std::vector<Complex> points_rotation;
    Complex rotation;
    rotation.x = 1 / 2;
    rotation.y = sqrt(3) / 2;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] * rotation;
        points_rotation.push_back(complex);
    }

    cv::Mat blank_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = 0; j < points_rotation.size(); ++j)
        {
            cv::line(blank_image, cv::Point(points[i].x + 400, points[i].y + 400), cv::Point(points[i + 1].x + 400, points[i + 1].y + 400), cv::Scalar(0, 200, 0));
            cv::line(blank_image, cv::Point(points[points.size() - 1].x + 400, points[points.size() - 1].y + 400), cv::Point(points[0].x + 400, points[0].y + 400), cv::Scalar(0, 200, 0));
            cv::line(blank_image, cv::Point(points_rotation[j].x + 400, points_rotation[j].y + 400), cv::Point(points_rotation[j + 1].x + 400, points_rotation[j + 1].y + 400), cv::Scalar(0, 0, 200));
            cv::line(blank_image, cv::Point(points_rotation[points_rotation.size() - 1].x + 400, points_rotation[points_rotation.size() - 1].y + 400), cv::Point(points_rotation[0].x + 400, points_rotation[0].y + 400), cv::Scalar(0, 0, 200));
        }
    }

    cv::flip(blank_image, blank_image, 0);
    cv::imshow("blank_image", blank_image);
    cv::waitKey(0);
}