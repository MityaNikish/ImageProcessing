#include "ChangeBrightness.hpp"


ChangeBrightness::ChangeBrightness(double coef_brightness) : coef_brightness_(coef_brightness)
{
	if (coef_brightness < 0.0)
	{
        coef_brightness_ = 0.0;
	}
    if (coef_brightness > 1.0)
    {
        coef_brightness_ = 1.0;
    }
}

void ChangeBrightness::addEffect(cv::Mat& img_changing, const cv::Mat& img_initial, const cv::Rect roi_rect_slice)
{
    cv::Mat slice = img_initial(roi_rect_slice).clone();
    const uint8_t deep = static_cast<uint8_t>(coef_brightness_ * 255);
    slice += cv::Scalar(deep, deep, deep);
    cv::Rect roi(roi_rect_slice.x, roi_rect_slice.y, roi_rect_slice.width, roi_rect_slice.height);
    //std::lock_guard<std::mutex> lock(mutex);
    slice.copyTo(img_changing(roi));
}