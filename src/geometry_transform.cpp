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

Complex get_rotation_point(const Complex& source_point, const Complex& rotation)
{
    Complex destination_point;
    destination_point = source_point * rotation;
    return destination_point;
}

Complex get_shear(const Complex& source_point, float scale)
{
    Complex destination_point;
    destination_point.x = source_point.x + source_point.y * scale;
    destination_point.y = source_point.y;
    return destination_point;
}

Complex get_scaling(const Complex& source_point, Complex scale)
{
    Complex destination_point;
    destination_point.x = source_point.x * scale.x;
    destination_point.y = source_point.y * scale.y;
    return destination_point;
}

Complex get_reflection_point(const Complex& source_point)
{
    Complex destination_point;
    destination_point.x = -source_point.x;
    destination_point.y = source_point.y;
    return destination_point;
}

Complex get_translation_point(const Complex& source_point, const Complex& translation)
{
    Complex translation_point;
    translation_point = source_point + translation;
    return translation_point;
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

    Complex rotate;
    rotate.x = cos(M_PI / 3);
    rotate.y = sin(M_PI / 3);
    std::vector<Complex> rotation_points;
    Complex destination_point_rotation;
    for (size_t i = 0; i < points.size(); ++i)
    {
        destination_point_rotation = get_rotation_point(points[i], rotate);
        rotation_points.push_back(destination_point_rotation);
    }

    Complex translation;
    translation.x = 50;
    translation.y = 100;
    std::vector<Complex> translation_points;
    Complex translation_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        translation_point = get_translation_point(points[i], translation);
        translation_points.push_back(translation_point);
    }

    std::vector<Complex> reflection_points;
    Complex reflection_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        reflection_point = get_reflection_point(points[i]);
        reflection_points.push_back(reflection_point);
    }

    float shear = 1;
    std::vector<Complex> shear_points;
    Complex shear_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        shear_point = get_shear(points[i], shear);
        shear_points.push_back(shear_point);
    }

    Complex scale_uniform(0.5, 0.5);
    std::vector<Complex> scale_uniform_points;
    Complex scale_uniform_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scale_uniform_point = get_scaling(points[i], scale_uniform);
        scale_uniform_points.push_back(scale_uniform_point);
    }

    Complex scale_nouniform(1, 2);
    std::vector<Complex> scale_nouniform_points;
    Complex scale_nouniform_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        scale_nouniform_point = get_scaling(points[i], scale_nouniform);
        scale_nouniform_points.push_back(scale_nouniform_point);
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
