#pragma once
#include "Effect.hpp"

class InvertColors final : public Effect
{
public:
    InvertColors() = default;
    void addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice) override;

    InvertColors(const InvertColors&) = default;
    InvertColors& operator=(const InvertColors&) = default;
    InvertColors(InvertColors&&) = default;
    InvertColors& operator=(InvertColors&&) = default;
    ~InvertColors() override = default;
};