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

void draw_transform(cv::Mat& image, const std::vector<Complex>& source_points, const std::vector<Complex>& destination_points)
{
    int mid = image.rows / 2;
    int top = image.rows;
    cv::line(image, cv::Point(mid, 0), cv::Point(mid, top), cv::Scalar(100, 0, 0));
    cv::line(image, cv::Point(0, mid), cv::Point(top, mid), cv::Scalar(100, 0, 0));
    draw_polygon(image, source_points, Complex(mid, mid), cv::Scalar(0, 255, 0));
    draw_polygon(image, destination_points, Complex(mid, mid), cv::Scalar(0, 0, 255));
}

int main()
{
    std::vector<Complex> points;
    for (size_t i = 0; i < 10; ++i)
    {
        points.push_back(Complex(rand() % 200, rand() % 200));
    }

    Complex rotate(cos(M_PI / 3), sin(M_PI / 3));
    std::vector<Complex> rotation_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex destination_point_rotation = Complex::get_rotation_point(points[i], rotate);
        rotation_points.push_back(destination_point_rotation);
    }

    Complex translation(50, 100);
    std::vector<Complex> translation_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        Complex translation_point = Complex::get_translation_point(points[i], translation);
        translation_points.push_back(translation_point);
    }

    std::vector<Complex> reflection_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        reflection_points.push_back(Complex::get_reflection_point(points[i]));
    }

    float shear = 1;
    std::vector<Complex> shear_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        shear_points.push_back(Complex::get_shear(points[i], shear));
    }

    Complex scale_uniform(0.5, 0.5);
    std::vector<Complex> scale_uniform_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scale_uniform_points.push_back(Complex::get_scaling(points[i], scale_uniform));
    }

    Complex scale_nouniform(1, 2);
    std::vector<Complex> scale_nouniform_points;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scale_nouniform_points.push_back(Complex::get_scaling(points[i], scale_nouniform));
    }

    cv::Mat rotation_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(rotation_image, points, rotation_points);
    cv::flip(rotation_image, rotation_image, 0);
    cv::imshow("rotation_image", rotation_image);

    cv::Mat translation_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(translation_image, points, translation_points);
    cv::flip(translation_image, translation_image, 0);
    cv::imshow("translation_image", translation_image);

    cv::Mat reflection_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(reflection_image, points, reflection_points);
    cv::flip(reflection_image, reflection_image, 0);
    cv::imshow("reflection_image", reflection_image);

    cv::Mat shear_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(shear_image, points, shear_points);
    cv::flip(shear_image, shear_image, 0);
    cv::imshow("shear_image", shear_image);

    cv::Mat scale_uniform_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(scale_uniform_image, points, scale_uniform_points);
    cv::flip(scale_uniform_image, scale_uniform_image, 0);
    cv::imshow("scale_uniform_image", scale_uniform_image);

    cv::Mat scale_nouniform_image(cv::Size(800, 800), CV_8UC3, cv::Scalar(0, 0, 0));
    draw_transform(scale_nouniform_image, points, scale_nouniform_points);
    cv::flip(scale_nouniform_image, scale_nouniform_image, 0);
    cv::imshow("scale_nouniform_image", scale_nouniform_image);


    cv::waitKey(0);
}
