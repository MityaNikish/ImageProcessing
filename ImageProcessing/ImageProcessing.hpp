#pragma once
#include <opencv2/opencv.hpp>
#include <future>
#include "Effect.hpp"


class ImageProcessing final
{
    std::unique_ptr<Effect> strategy;
    unsigned numThreads_;
    std::vector<std::future<void>> futures;
public:

    ImageProcessing();
    ImageProcessing(unsigned numThreads);
    void setStrategy(std::unique_ptr<Effect> new_strategy);
    cv::Mat useStrategy(const cv::Mat& img);
};