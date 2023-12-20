#include "ImageProcessing.hpp"
#include "my_exceptions.hpp"
#include "ThreadPool.hpp"


ImageProcessing::ImageProcessing() : num_threads_(std::thread::hardware_concurrency()) {}

ImageProcessing::ImageProcessing(const unsigned num_threads) : num_threads_(num_threads > 0 ? num_threads : std::thread::hardware_concurrency()) { }

void ImageProcessing::setEffect(std::unique_ptr<Effect> new_strategy)
{
    effect_ = std::move(new_strategy);
}

//cv::Mat ImageProcessing::useStrategy(const cv::Mat& img)
//{
//    Effect* parent_ptr = strategy.get();
//    //void (Strategy::*strtg)(cv::Mat&, int) = &Strategy::add_effect;
//
//    cv::Mat new_img(img);
//    if (!strategy)
//    {
//        throw not_selected_strategy();
//    }
//
//    for (int number_row = 0; number_row < new_img.rows; ++number_row)
//    {
//        // Запускаем потоки асинхронно и добавляя результат в вектор futures
//        //futures.push_back(std::async(std::launch::async, strategy->add_effect, std::ref(new_img), number_row));
//        futures.push_back(std::async([parent_ptr, &new_img, number_row] {  return parent_ptr->add_effect(new_img, number_row); }));
//
//        // Если достигнуто максимальное количество потоков, ждем завершения одного из них
//        if (futures.size() == numThreads_)
//        {
//            for (auto& future : futures)
//            {
//                future.get();
//            }
//            futures.clear();
//        }
//    }
//
//    // Ждем завершения оставшихся потоков
//    for (auto& future : futures) {
//        future.get();
//    }
//
//    return new_img;
//}

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
        cv::Rect roi_rect(0, decent_number_slice * step_y, width,  (decent_number_slice == quantity_slices - 1) ? height - decent_number_slice * step_y : step_y);
        cv::Mat slice = img(roi_rect).clone();
        pool.enqueue([this, &new_img , slice] {  return effect_->addEffect(new_img, slice); });
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
        cv::Rect roi_rect(0, decent_number_slice * step_y, width, (decent_number_slice == quantity_slices - 1) ? height - decent_number_slice * step_y : step_y);
        cv::Mat slice = img(roi_rect).clone();
        effect_->addEffect(new_img, slice);
    }

    return new_img;
}