#pragma once
#include <opencv2/opencv.hpp>


class Effect
{
public:
    virtual void addEffect(cv::Mat& img, const cv::Mat slice) = 0;
    virtual ~Effect() = default;
};