#include "ImageProcessing.hpp"
#include "MyExceptions.hpp"
#include "ThreadPool.hpp"


ImageProcessing::ImageProcessing() : num_threads_(std::thread::hardware_concurrency()) {}

ImageProcessing::ImageProcessing(const unsigned num_threads) : num_threads_(num_threads > 0 ? num_threads : std::thread::hardware_concurrency()) { }

void ImageProcessing::setEffect(std::unique_ptr<Effect> new_effect)
{
    effect_ = std::move(new_effect);
}

cv::Mat ImageProcessing::applyEffect(const cv::Mat& img, const uint8_t quantity_slices) const
{
    if (!effect_)
    {
        throw not_selected_strategy();
    }

    ThreadPool pool(num_threads_);
    cv::Mat new_img(img);
    const int width = new_img.cols;
    const int height = new_img.rows;
    const int step_y = height / static_cast<int>(quantity_slices);

    for (int decent_number_slice = 0; decent_number_slice < quantity_slices; ++decent_number_slice)
    {
        const cv::Rect roi_rect_slice(0, decent_number_slice * step_y, width,  (decent_number_slice == quantity_slices - 1) ? height - decent_number_slice * step_y : step_y);
        pool.enqueue([this, &new_img, &img, &roi_rect_slice] {  return effect_->addEffect(new_img, img, roi_rect_slice); });
    }

    return new_img;
}

cv::Mat ImageProcessing::applyEffectSubsequently(const cv::Mat& img, const uint8_t quantity_slices) const
{
    if (!effect_)
    {
        throw not_selected_strategy();
    }

    cv::Mat new_img(img);
    const int width = new_img.cols;
    const int height = new_img.rows;
    const int step_y = height / static_cast<int>(quantity_slices);

    for (int decent_number_slice = 0; decent_number_slice < quantity_slices; ++decent_number_slice)
    {
        const cv::Rect roi_rect_slice(0, decent_number_slice * step_y, width, (decent_number_slice == quantity_slices - 1) ? height - decent_number_slice * step_y : step_y);
        effect_->addEffect(new_img, img, roi_rect_slice);
    }

    return new_img;
}

//cv::Mat ImageProcessing::applyEffect(const cv::Mat& img, const uint8_t quantity_slices) const
//{
//    auto effectFunction = [this](cv::Mat& new_img, const cv::Mat& img, const cv::Rect& roi_rect_slice) {
//        pool_.enqueue([this, &new_img, &img, &roi_rect_slice] { return effect_->addEffect(new_img, img, roi_rect_slice); });
//        };
//
//    return applyEffectHelper(img, quantity_slices, effectFunction);
//}
//
//cv::Mat ImageProcessing::applyEffectSubsequently(const cv::Mat& img, const uint8_t quantity_slices) const
//{
//    auto effect_function = [this](cv::Mat& new_img, const cv::Mat& img, const cv::Rect& roi_rect_slice){
//        effect_->addEffect(new_img, img, roi_rect_slice);
//        };
//
//    return applyEffectHelper(img, quantity_slices, effect_function);
//}
//
//cv::Mat ImageProcessing::applyEffectHelper(const cv::Mat& img, const uint8_t quantity_slices, const std::function<void(cv::Mat&, const cv::Mat&, const cv::Rect&)>& effect_function) const
//{
//    if (!effect_)
//    {
//        throw not_selected_strategy();
//    }
//
//    cv::Mat new_img(img);
//    const int width = new_img.cols;
//    const int height = new_img.rows;
//    const int step_y = height / static_cast<int>(quantity_slices);
//
//    for (int decent_number_slice = 0; decent_number_slice < quantity_slices; ++decent_number_slice)
//    {
//        const cv::Rect roi_rect_slice(0, decent_number_slice * step_y, width, (decent_number_slice == quantity_slices - 1) ? height - decent_number_slice * step_y : step_y);
//        effect_function(new_img, img, roi_rect_slice);
//    }
//
//    return new_img;
//}