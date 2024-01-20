#include "ImageProcessing.hpp"
#include "MyExceptions.hpp"
#include "ThreadPool.hpp"


ImageProcessing::ImageProcessing() : num_threads_(std::thread::hardware_concurrency()) {}

ImageProcessing::ImageProcessing(const unsigned num_threads) : num_threads_(num_threads) { }

void ImageProcessing::setEffect(std::unique_ptr<Effect> new_effect)
{
    effect_ = std::move(new_effect);
}

cv::Mat ImageProcessing::applyEffect(const cv::Mat& img, unsigned quantity_slices)
{
    if (!effect_)
    {
        throw not_selected_strategy();
    }

    if (quantity_slices == 0)
    {
        quantity_slices = img.cols * img.rows / 250000;
    }

    ThreadPool pool(num_threads_);
    cv::Mat new_img(img);
    const int width = new_img.cols;
    const int height = new_img.rows;
    const int step_y = height / quantity_slices;

    for (int decent_number_slice = 0; decent_number_slice < static_cast<int>(quantity_slices); ++decent_number_slice)
    {
        const cv::Rect roi_rect_slice(0, decent_number_slice * step_y, width,  (decent_number_slice == static_cast<int>(quantity_slices) - 1) ? height - decent_number_slice * step_y : step_y);
        futures_.emplace_back(pool.enqueue([this, &new_img, img, roi_rect_slice] {  return effect_->addEffect(new_img, img, roi_rect_slice); }));
    }

	std::ranges::for_each(futures_.begin(), futures_.end(), [](std::future<void>& f){ f.get(); });
    futures_.clear();

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
