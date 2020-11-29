#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <stdio.h>

#include "complex/complex.hpp"

void scaling_image(cv::Mat& blank_image, std::vector<Complex> points, float scale)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;
    std::vector<Complex> points_scaling;
    Complex scaling;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scaling.x = points[i].x * scale;
        scaling.y = points[i].y * scale;
        points_scaling.push_back(scaling);
    }
    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1) % points.size()].x + mid, points[(i + 1) % points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_scaling[i].x + mid, points_scaling[i].y + mid), cv::Point(points_scaling[(i + 1) % points_scaling.size()].x + mid, points_scaling[(i + 1) % points_scaling.size()].y + mid), cv::Scalar(0, 0, 200));
    }

    cv::line(blank_image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(blank_image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
}

void reflection_image(cv::Mat& blank_image, std::vector<Complex> points)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;
    std::vector<Complex> points_reflection;
    Complex reflection;
    for (size_t i = 0; i < points.size(); ++i)
    {
        reflection.x = -points[i].x;
        reflection.y = points[i].y;
        points_reflection.push_back(reflection);
    }
    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1) % points.size()].x + mid, points[(i + 1) % points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_reflection[i].x + mid, points_reflection[i].y + mid), cv::Point(points_reflection[(i + 1) % points_reflection.size()].x + mid, points_reflection[(i + 1) % points_reflection.size()].y + mid), cv::Scalar(0, 0, 200));
    }

    cv::line(blank_image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(blank_image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
}

void rotation_image(cv::Mat& blank_image, Complex rotation_point, std::vector<Complex> points)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;

    std::vector<Complex> points_rotation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] * rotation_point;
        points_rotation.push_back(complex);
    }

    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1) % points.size()].x + mid, points[(i + 1) % points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_rotation[i].x + mid, points_rotation[i].y + mid), cv::Point(points_rotation[(i + 1) % points_rotation.size()].x + mid, points_rotation[(i + 1) % points_rotation.size()].y + mid), cv::Scalar(0, 0, 200));
    }

    cv::line(blank_image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(blank_image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
}

void translation_image(cv::Mat& blank_image, Complex translation_point, std::vector<Complex> points)
{
    int mid = blank_image.rows / 2;
    int top = blank_image.rows;

    std::vector<Complex> points_translation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex complex;
        complex = points[i] + translation_point;
        points_translation.push_back(complex);
    }
    for (size_t i = 0; i < points.size(); ++i)
    {
        cv::line(blank_image, cv::Point(points[i].x + mid, points[i].y + mid), cv::Point(points[(i + 1) % points.size()].x + mid, points[(i + 1) % points.size()].y + mid), cv::Scalar(0, 200, 0));
        cv::line(blank_image, cv::Point(points_translation[i].x + mid, points_translation[i].y + mid), cv::Point(points_translation[(i + 1) % points_translation.size()].x + mid, points_translation[(i + 1) % points_translation.size()].y + mid), cv::Scalar(0, 0, 200));
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

    Complex rotation_point;
    rotation_point.x = cos(M_PI / 3);
    rotation_point.y = sin(M_PI / 3);

    Complex translation_point;
    translation_point.x = 50;
    translation_point.y = 100;

    float scale = 0.5;

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