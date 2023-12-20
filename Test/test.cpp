#include "pch.h"
#include <chrono>
#include <iostream>

#include "ImageProcessing.hpp"
#include "InvertColors.hpp"



int main()
{
    ImageProcessing image_processing(2);
    image_processing.setEffect(std::make_unique<InvertColors>());

    cv::Mat input_image = cv::imread("bird.jpg");

    if (input_image.empty()) {
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = image_processing.applyEffectSubsequently(input_image);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);

    cv::imshow("Image", output_image);
    cv::waitKey(0);

    return 0;
}


//int main()
//{
//    ImageProcessing img_proc(1);
//    img_proc.setEffect(std::make_unique<InvertColors>());
//
//    cv::Mat input_image = cv::imread("bird.jpg");
//
//    if (input_image.empty()) {
//        std::cerr << "Error: Unable to load input image." << std::endl;
//    }
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//    cv::Mat output_image = img_proc.applyEffect(input_image);
//    auto end_time = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//    std::cout << "Working hours: " << duration << std::endl;
//
//    //cv::imwrite("output_image.jpg", outputImage);
//
//    cv::imshow("Image", output_image);
//    cv::waitKey(0);
//
//    return 0;
//}
//
//TEST(Test_InvertColors, AllThreads)
//{
//    ImageProcessing img_proc;
//    img_proc.setEffect(std::make_unique<InvertColors>());
//
//    cv::Mat input_image = cv::imread("bird.jpg");
//
//    if (input_image.empty()) {
//        std::cerr << "Error: Unable to load input image." << std::endl;
//    }
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//    cv::Mat output_image = img_proc.applyEffect(input_image);
//    auto end_time = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//    std::cout << "Working hours: " << duration << std::endl;
//
//    //cv::imwrite("output_image.jpg", outputImage);
//}
//
//
//TEST(Test_InvertColors, OneThreads)
//{
//    ImageProcessing img_proc(1);
//    img_proc.setEffect(std::make_unique<InvertColors>());
//
//    cv::Mat input_image = cv::imread("bird.jpg");
//
//    if (input_image.empty()) {
//        std::cerr << "Error: Unable to load input image." << std::endl;
//    }
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//    cv::Mat output_image = img_proc.applyEffect(input_image);
//    auto end_time = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//    std::cout << "Working hours: " << duration << std::endl;
//
//    //cv::imwrite("output_image.jpg", outputImage);
//}
//
//
//TEST(Test_InvertColors, OverMoreThreads)
//{
//    ImageProcessing img_proc(100);
//    img_proc.setEffect(std::make_unique<InvertColors>());
//
//    cv::Mat input_image = cv::imread("bird.jpg");
//
//    if (input_image.empty()) {
//        std::cerr << "Error: Unable to load input image." << std::endl;
//    }
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//    cv::Mat output_image = img_proc.applyEffect(input_image);
//    auto end_time = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//    std::cout << "Working hours: " << duration << std::endl;
//
//    //cv::imwrite("output_image.jpg", outputImage);
//}
