#include "Blur.hpp"


Blur::Blur(cv::Size kernel_size, double sigma_x, double sigma_y, int border_type) :
	kernel_size_(kernel_size), sigma_x_(sigma_x), sigma_y_(sigma_y), border_type_(border_type) {}


void Blur::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
{
    const int step_up = roi_rect_slice.y < kernel_size_.height ? roi_rect_slice.y : kernel_size_.height;
    const int step_down = roi_rect_slice.y + roi_rect_slice.height + kernel_size_.height > img_initial.cols ? img_initial.cols - roi_rect_slice.y - roi_rect_slice.height : kernel_size_.height;
    cv::Rect roi_rect_slice_plus(roi_rect_slice.x, roi_rect_slice.y - step_up, roi_rect_slice.width, roi_rect_slice.height + step_down);
    cv::Mat slice = img_initial(roi_rect_slice_plus).clone();
    cv::GaussianBlur(slice, slice, kernel_size_, sigma_x_, sigma_y_, border_type_);
    const cv::Mat slice_new = slice(cv::Rect(roi_rect_slice.x, step_up, roi_rect_slice.width, roi_rect_slice.height)).clone();
    slice_new.copyTo(img_changing(roi_rect_slice));
}
