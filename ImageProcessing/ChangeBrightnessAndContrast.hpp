#pragma once
#include "Effect.hpp"

class ChangeBrightnessAndContrast final : public Effect
{
    double alpha_brightness_;
    double beta_contrast_;

public:
    ChangeBrightnessAndContrast(const double alpha_brightness = 1, const double beta_contrast = 0);
    void addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice) override;

    ChangeBrightnessAndContrast(const ChangeBrightnessAndContrast&) = default;
    ChangeBrightnessAndContrast& operator=(const ChangeBrightnessAndContrast&) = default;
    ChangeBrightnessAndContrast(ChangeBrightnessAndContrast&&) = default;
    ChangeBrightnessAndContrast& operator=(ChangeBrightnessAndContrast&&) = default;
    ~ChangeBrightnessAndContrast() override = default;
};