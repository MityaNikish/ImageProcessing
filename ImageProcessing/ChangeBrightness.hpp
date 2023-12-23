#pragma once
#include "Effect.hpp"

class ChangeBrightness final : public Effect
{
    double coef_brightness_;

public:
    ChangeBrightness(const double coef_brightness);
    void addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice) override;

    ChangeBrightness(const ChangeBrightness&) = default;
    ChangeBrightness& operator=(const ChangeBrightness&) = default;
    ChangeBrightness(ChangeBrightness&&) = default;
    ChangeBrightness& operator=(ChangeBrightness&&) = default;
    ~ChangeBrightness() override = default;
};