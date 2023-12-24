#include "Blur.hpp"

namespace 
{
    cv::Mat boxBlur(cv::Mat& img, int window_size)
	{
        int half_window_size = window_size / 2;
        for (int y = half_window_size; y < img.rows - half_window_size; ++y)
        {
            for (int x = half_window_size; x < img.cols - half_window_size; ++x)
            {
                cv::Vec<unsigned, 3> sum = 0;
                for (int wy = -half_window_size; wy <= half_window_size; ++wy) 
                {
                    for (int wx = -half_window_size; wx <= half_window_size; ++wx)
                    {
                        sum += img.at<cv::Vec3b>(y + wy, x + wx);
                    }
                }
                img.at<cv::Vec3b>(y, x) = sum / (window_size * window_size);
            }
        }
        return img;
    }
}


Blur::Blur(cv::Size kernel_size, double sigma_x, double sigma_y, int border_type) :
	kernel_size_(kernel_size), sigma_x_(sigma_x), sigma_y_(sigma_y), border_type_(border_type) {}


void Blur::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
{
    const int step_up = roi_rect_slice.y < kernel_size_.height ? roi_rect_slice.y : kernel_size_.height;
    const int step_down = roi_rect_slice.y + roi_rect_slice.height + kernel_size_.height > img_initial.cols ? img_initial.cols - roi_rect_slice.y - roi_rect_slice.height : kernel_size_.height;
    cv::Rect roi_rect_slice_plus(roi_rect_slice.x, roi_rect_slice.y - step_up, roi_rect_slice.width, roi_rect_slice.height + step_down);
    cv::Mat slice = img_initial(roi_rect_slice_plus).clone();
    cv::GaussianBlur(slice, slice, kernel_size_, sigma_x_, sigma_y_, border_type_);
    //slice = boxBlur(slice, kernel_size_.height);
    const cv::Mat slice_new = slice(cv::Rect(roi_rect_slice.x, step_up, roi_rect_slice.width, roi_rect_slice.height)).clone();
    slice_new.copyTo(img_changing(roi_rect_slice));
}

//void Blur::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
//{
//    cv::Mat slice = img_initial(roi_rect_slice).clone();
//    cv::GaussianBlur(slice, slice, kernel_size_, sigma_x_, sigma_y_, border_type_);
//    //slice = boxBlur(slice, kernel_size_.height);
//    slice.copyTo(img_changing(roi_rect_slice));
//}