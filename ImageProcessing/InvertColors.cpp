#include "InvertColors.hpp"


void InvertColors::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
{
    cv::Mat slice = img_initial(roi_rect_slice).clone();
    cv::bitwise_not(slice, slice);
    const cv::Rect roi(roi_rect_slice.x, roi_rect_slice.y, roi_rect_slice.width, roi_rect_slice.height);
    //std::lock_guard<std::mutex> lock(mutex);
    slice.copyTo(img_changing(roi));
}