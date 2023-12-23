#pragma once
#include <opencv2/opencv.hpp>
#include "Effect.hpp"


class ImageProcessing final
{
    std::unique_ptr<Effect> effect_;
    unsigned num_threads_;

public:
    ImageProcessing();
    ImageProcessing(unsigned num_threads);
    void setEffect(std::unique_ptr<Effect> new_effect);
    cv::Mat applyEffect(const cv::Mat& img, const uint8_t quantity_slices = 20) const;
    cv::Mat applyEffectSubsequently(const cv::Mat& img, const uint8_t quantity_slices = 20) const;

    ImageProcessing(const ImageProcessing&) = delete;
    ImageProcessing(ImageProcessing&&) = default;
    ImageProcessing& operator=(const ImageProcessing&) = delete;
    ImageProcessing& operator=(ImageProcessing&&) = default;
    ~ImageProcessing() = default;

private:
    cv::Mat applyEffectHelper(const cv::Mat& img, const uint8_t quantity_slices, const std::function<void(cv::Mat&, const cv::Mat&, const cv::Rect&)>& effect_function) const;
};