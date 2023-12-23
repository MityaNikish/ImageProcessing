#pragma once
#include <opencv2/opencv.hpp>

//inline std::mutex mutex;

class Effect
{
public:
    virtual void addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice) = 0;
    virtual ~Effect() = default;
};