#pragma once
#include <opencv2/opencv.hpp>
#include <future>
#include "Effect.hpp"


class ImageProcessing final
{
    std::vector<std::future<void>> futures_;
    std::unique_ptr<Effect> effect_;
    unsigned num_threads_;

public:
    ImageProcessing();
    explicit ImageProcessing(unsigned num_threads);
    void setEffect(std::unique_ptr<Effect> new_effect);
    cv::Mat applyEffect(const cv::Mat& img, unsigned quantity_slices = 0);
    cv::Mat applyEffectSubsequently(const cv::Mat& img, const uint8_t quantity_slices = 20) const;

    ImageProcessing(const ImageProcessing&) = delete;
    ImageProcessing(ImageProcessing&&) = default;
    ImageProcessing& operator=(const ImageProcessing&) = delete;
    ImageProcessing& operator=(ImageProcessing&&) = default;
    ~ImageProcessing() = default;
};