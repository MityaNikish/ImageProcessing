#include "ImageProcessing.hpp"
#include "my_exceptions.hpp"
#include <thread>


ImageProcessing::ImageProcessing() : numThreads_(std::thread::hardware_concurrency()) {}
ImageProcessing::ImageProcessing(unsigned numThreads) : numThreads_(numThreads)
{
    const unsigned max_num_threads = std::thread::hardware_concurrency();
    numThreads_ = (numThreads > 0 && numThreads <= max_num_threads) ? numThreads : max_num_threads;
}

void ImageProcessing::setStrategy(std::unique_ptr<Effect> new_strategy)
{
    strategy = std::move(new_strategy);
}

cv::Mat ImageProcessing::useStrategy(const cv::Mat& img)
{
    Effect* parent_ptr = strategy.get();
    //void (Strategy::*strtg)(cv::Mat&, int) = &Strategy::add_effect;

    cv::Mat new_img(img);
    if (!strategy)
    {
        throw not_selected_strategy();
    }

    for (int number_row = 0; number_row < new_img.rows; ++number_row)
    {
        // ��������� ������ ���������� � �������� ��������� � ������ futures
        //futures.push_back(std::async(std::launch::async, strategy->add_effect, std::ref(new_img), number_row));
        futures.push_back(std::async([parent_ptr, &new_img, number_row] {  return parent_ptr->add_effect(new_img, number_row); }));

        // ���� ���������� ������������ ���������� �������, ���� ���������� ������ �� ���
        if (futures.size() == numThreads_)
        {
            for (auto& future : futures)
            {
                future.get();
            }
            futures.clear();
        }
    }

    // ���� ���������� ���������� �������
    for (auto& future : futures) {
        future.get();
    }

    return new_img;
}
