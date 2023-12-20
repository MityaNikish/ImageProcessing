#include "InvertColors.hpp"

std::mutex resultMutex;

void InvertColors::addEffect(cv::Mat& img, const cv::Mat slice)
{
    //int width = img.cols;
    //int height = img.rows;

    //for (int y = 0; y < height; y++)
    //{
    //    for (int x = 0; x < width; x++)
    //    {
    //        //cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
    //        //pixel = cv::Vec3b(0, 0, 0);

    //        cv::Vec3b* pixel = img.ptr<cv::Vec3b>(y, x);
    //        *pixel = cv::Vec3b(0, 0, 0);
    //    }
    //}
    cv::Mat processed_slice = slice;
    //cv::addWeighted(slice, 1.5, cv::Mat(), 0, 0, processedSlice);
    processed_slice += cv::Scalar(50, 50, 50);
    cv::Mat x = processed_slice.colRange(0, 1);
    cv::Mat y = processed_slice.rowRange(0, 1);

    cv::Rect roi(0, 0, processed_slice.cols, processed_slice.rows);

    //std::lock_guard<std::mutex> lock(resultMutex);
    processed_slice.copyTo(img(roi));

    //cv::imshow("Check", processedSlice);
    //cv::waitKey(0);

    //cv::bitwise_not(img, img);
}