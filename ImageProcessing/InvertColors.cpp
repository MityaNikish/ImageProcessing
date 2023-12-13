#include "InvertColors.hpp"


void InvertColors::add_effect(cv::Mat& img, int number_row)
{
    cv::Vec3b* ptr = img.ptr<cv::Vec3b>(number_row);
    for (int number_col = 0; number_col < img.cols; number_col++) {
        ptr[number_col] = cv::Vec3b(255 - ptr[number_col][0], 255 - ptr[number_col][1],  255 - ptr[number_col][2]);
    }
}