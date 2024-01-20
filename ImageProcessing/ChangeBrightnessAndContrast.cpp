#include "ChangeBrightnessAndContrast.hpp"


ChangeBrightnessAndContrast::ChangeBrightnessAndContrast(const double alpha_brightness, const double beta_contrast) :
	alpha_brightness_(alpha_brightness), beta_contrast_(beta_contrast) {}

void ChangeBrightnessAndContrast::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
{
    cv::Mat slice = img_initial(roi_rect_slice).clone();
    slice.convertTo(slice, -1, alpha_brightness_, beta_contrast_);
    cv::Rect roi(roi_rect_slice.x, roi_rect_slice.y, roi_rect_slice.width, roi_rect_slice.height);
    slice.copyTo(img_changing(roi));
}