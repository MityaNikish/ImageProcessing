#include "pch.h"

#include <chrono>
#include <iostream>

#include "MyExceptions.hpp"
#include "ImageProcessing.hpp"
#include "InvertColors.hpp"
#include "ChangeBrightness.hpp"
#include "Blur.hpp"

#include "ThreadPool.hpp"

namespace 
{
    std::string img_path = "../stuff/16k.jpg";

    void my_thread_sleep_for()
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}



TEST(Test_ThreadPool, MultiThreads)
{
    ThreadPool pool(std::thread::hardware_concurrency());
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        pool.enqueue(my_thread_sleep_for);
    }
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    EXPECT_TRUE(duration.count() < 5500); // всего 50000 mks
}


TEST(Test_Exception, Strategy)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    EXPECT_THROW(img_proc.applyEffect(input_image), not_selected_strategy);

}


TEST(Test_InvertColors, MultiThreads)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<InvertColors>());

    const cv::Mat input_image = cv::imread(img_path);

    
    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffect(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours MultiThreads InvertColors: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}


TEST(Test_InvertColors, Subsequently)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<InvertColors>());

    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffectSubsequently(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours Subsequently InvertColors: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}

TEST(Test_ChangeBrightness, MultiThreads)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<ChangeBrightness>(0.5));

    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffect(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours MultiThreads ChangeBrightness: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}


TEST(Test_ChangeBrightness, Subsequently)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<ChangeBrightness>(0.5));

    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffectSubsequently(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours Subsequently ChangeBrightness: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}

TEST(Test_Blur, MultiThreads)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<Blur>(cv::Size(5, 5), 5, 5));

    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty()) 
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffect(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours MultiThreads Blur: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}


TEST(Test_Blur, Subsequently)
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing img_proc;
    img_proc.setEffect(std::make_unique<Blur>(cv::Size(5, 5), 5, 5));

    const cv::Mat input_image = cv::imread(img_path);

    if (input_image.empty())
    {
        EXPECT_TRUE(false);
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat output_image = img_proc.applyEffectSubsequently(input_image);
    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours Subsequently Blur: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}