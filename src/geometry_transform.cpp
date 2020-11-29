#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <stdio.h>

#include "complex/complex.hpp"

void draw_polygon(cv::Mat& image, const std::vector<Complex>& points, const Complex& offset, const cv::Scalar& colour)
{
    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(image, cv::Point(points[i].x + offset.x, points[i].y + offset.y), cv::Point(points[(i + 1) % points.size()].x + offset.x, points[(i + 1) % points.size()].y + offset.y), colour);
    }
}

void draw_transform(cv::Mat& image, const std::vector<Complex>& source_points, std::vector<Complex>& destination_points)
{
    int mid = image.rows / 2;
    int top = image.rows;
    cv::line(image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
    draw_polygon(image, source_points, Complex(mid, mid), cv::Scalar(0, 255, 0));
    draw_polygon(image, destination_points, Complex(mid, mid), cv::Scalar(0, 0, 255));
}

void scaling_image(cv::Mat& blank_image, const std::vector<Complex>& points, float scale)
{
    std::vector<Complex> points_scaling;
    Complex scaling;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scaling.x = points[i].x + points[i].y * scale;
        scaling.y = points[i].y;
        points_scaling.push_back(scaling);
    }
    draw_transform(blank_image, points, points_scaling);
}

void reflection_image(cv::Mat& blank_image, const std::vector<Complex>& points)
{
    std::vector<Complex> points_reflection;
    Complex reflection;
    for (size_t i = 0; i < points.size(); ++i)
    {
        reflection.x = -points[i].x;
        reflection.y = points[i].y;
        points_reflection.push_back(reflection);
    }
    draw_transform(blank_image, points, points_reflection);
}

void rotation_image(cv::Mat& blank_image, const Complex& rotation_point, const std::vector<Complex>& points)
{
    std::vector<Complex> points_rotation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] * rotation_point;
        points_rotation.push_back(complex);
    }
    draw_transform(blank_image, points, points_rotation);
}

void translation_image(cv::Mat& blank_image, const Complex& translation_point, const std::vector<Complex>& points)
{
    std::vector<Complex> points_translation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] + translation_point;
        points_translation.push_back(complex);
    }
    draw_transform(blank_image, points, points_translation);
}

int main()
{
    std::vector<Complex> points;
    Complex point;
    std::vector<int> numbers_x;
    std::vector<int> numbers_y;
    for (size_t i = 0; i < 10; ++i)
    {
        numbers_x.push_back(int(rand() % 200));
        numbers_y.push_back(int(rand() % 200));
    }
    for (size_t i = 0; i < numbers_x.size(); ++i)
    {
        point.x = numbers_x[i];
        point.y = numbers_y[i];
        points.push_back(point);
    }

    Complex rotation_point;
    rotation_point.x = cos(M_PI / 3);
    rotation_point.y = sin(M_PI / 3);

    Complex translation_point;
    translation_point.x = 50;
    translation_point.y = 100;

    float scale = 1;

    cv::Mat rotation(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    rotation_image(rotation, rotation_point, points);
    cv::flip(rotation, rotation, 0);
    cv::imshow("rotation", rotation);

    cv::Mat translation(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    translation_image(translation, translation_point, points);
    cv::flip(translation, translation, 0);
    cv::imshow("translation", translation);

    cv::Mat reflection(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    reflection_image(reflection, points);
    cv::flip(reflection, reflection, 0);
    cv::imshow("reflection", reflection);

    cv::Mat scale_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    scaling_image(scale_image, points, scale);
    cv::flip(scale_image, scale_image, 0);
    cv::imshow("scale_image", scale_image);

    cv::waitKey(0);
}