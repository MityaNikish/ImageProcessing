#pragma once
#include "Effect.hpp"

class InvertColors final : public Effect
{
public:
    void add_effect(cv::Mat& img, int number_row) override;
    ~InvertColors() override = default;
};