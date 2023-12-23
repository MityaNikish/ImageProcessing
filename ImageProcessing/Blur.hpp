#pragma once
#include "Effect.hpp"

class Blur final : public Effect
{
    cv::Size kernel_size_;
    double sigma_x_;
    double sigma_y_;
    int border_type_;

public:
    Blur(cv::Size kernel_size, double sigma_x, double sigma_y, int border_type = cv::BORDER_DEFAULT);
    void addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice) override;

    Blur(const Blur&) = default;
    Blur& operator=(const Blur&) = default;
    Blur(Blur&&) = default;
    Blur& operator=(Blur&&) = default;
    ~Blur() override = default;
};