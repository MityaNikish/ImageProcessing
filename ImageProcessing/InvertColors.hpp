#pragma once
#include "Effect.hpp"

class InvertColors final : public Effect
{
public:
    void addEffect(cv::Mat& img, const cv::Mat slice) override;
    ~InvertColors() override = default;
};