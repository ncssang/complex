#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <stdio.h>

#include "complex/complex.hpp"

void rotation_point(cv::Mat& blank_image, Complex rotation, std::vector<Complex> points)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;
    std::vector<Complex> points_rotation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] * rotation;
        points_rotation.push_back(complex);
    }

    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1)%points.size()].x + mid, points[(i + 1)%points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_rotation[i].x + mid, points_rotation[i].y + mid), cv::Point(points_rotation[(i + 1)%points_rotation.size()].x + mid, points_rotation[(i + 1)%points_rotation.size()].y + mid), cv::Scalar(0, 0, 200));
    }

    cv::line(blank_image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(blank_image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
}

void translation_point(cv::Mat& blank_image, Complex translation, std::vector<Complex> points)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;
    std::vector<Complex> points_translation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] + translation;
        points_translation.push_back(complex);
    }
    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1)%points.size()].x + mid, points[(i + 1)%points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_translation[i].x + mid, points_translation[i].y + mid), cv::Point(points_translation[(i + 1)%points_translation.size()].x + mid, points_translation[(i + 1)%points_translation.size()].y + mid), cv::Scalar(0, 0, 200));
    }

    cv::line(blank_image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(blank_image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
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

    Complex translation;
    translation.x = 50;
    translation.y = 100;

    Complex rotation;
    rotation.x = cos(M_PI / 3);
    rotation.y = sin(M_PI / 3);

    cv::Mat blank_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));

    // rotation_point(blank_image, rotation, points);
    translation_point(blank_image, translation, points);
    cv::flip(blank_image, blank_image, 0);
    cv::imshow("blank_image", blank_image);
    cv::waitKey(0);
}