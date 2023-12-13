#pragma once
#include <opencv2/opencv.hpp>

class Effect
{
public:
    virtual void add_effect(cv::Mat& img, int number_row) = 0;
    virtual ~Effect() = default;
};