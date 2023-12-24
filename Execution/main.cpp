#include <chrono>
#include <iostream>
#include <fstream>

#include <unordered_map>


#include "ImageProcessing.hpp"
#include "InvertColors.hpp"
#include "ChangeBrightness.hpp"
#include "Blur.hpp"

#include "ThreadPool.hpp"

namespace
{
    std::string img_path = "../stuff/bird.jpg";
}


void safeDate(const std::vector<std::tuple<int, int, long long >>& data)
{
    const std::string filename = "data.txt";
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error open file!" << std::endl;
        return;
    }

    for (auto& iter : data)
    {
        outFile << std::get<0>(iter) << '\t' << std::get<1>(iter) << '\t' << std::get<2>(iter) << std::endl;
    }

    outFile.close();
    std::cout << "Complete." << filename << std::endl;
}



//// quantity_slices = 40, number_threads = 3 <===== the best
//int main()
//{
//    cv::setNumThreads(1);
//    cv::setUseOptimized(false);
//    
//    cv::Mat input_image = cv::imread(img_path);
//    ImageProcessing image_processing;
//    image_processing.setEffect(std::make_unique<InvertColors>());
//
//    std::vector<std::tuple<int, int, long long>> data;
//
//    if (input_image.empty()) {
//        std::cerr << "Error: Unable to load input image." << std::endl;
//    }
//
//    for (uint8_t quantity_slices = 1; quantity_slices < 101; quantity_slices++)
//    {
//        std::cout << "Quantity slices: " << static_cast<unsigned>(quantity_slices) << "\n";
//        for (int number_threads = 1; number_threads < 25; number_threads++)
//        {
//            const auto start_time = std::chrono::high_resolution_clock::now();
//            cv::Mat output_image = image_processing.applyEffect(input_image, quantity_slices);
//            const auto end_time = std::chrono::high_resolution_clock::now();
//            const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//            //std::cout << "Working hours with " << number_threads << " = " << duration << "\n";
//            data.emplace_back(std::make_tuple(quantity_slices, number_threads, duration.count()));
//        }
//    }
//
//    safeDate(data);
//
//    return 0;
//}


int main()
{
    cv::setNumThreads(1);
    cv::setUseOptimized(false);

    ImageProcessing image_processing;

    //image_processing.setEffect(std::make_unique<InvertColors>());
    image_processing.setEffect(std::make_unique<ChangeBrightness>(0.5));
    //image_processing.setEffect(std::make_unique<Blur>(cv::Size(5, 5), 0, 0));

    const cv::Mat input_image = cv::imread(img_path);
    cv::Mat output_image;

    if (input_image.empty()) {
        std::cerr << "Error: Unable to load input image." << std::endl;
    }
    {
        const auto start_time = std::chrono::high_resolution_clock::now();
        output_image = image_processing.applyEffect(input_image);
        const auto end_time = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Working hours: " << duration << std::endl;
    }

    //cv::imwrite("../stuff/bird_1.jpg", output_image);

    cv::imshow("Image", output_image);
    cv::waitKey(0);

    return 0;
}




//int main()
//{
//    
//    const auto start_time = std::chrono::high_resolution_clock::now();
//    {
//        ThreadPool pool(std::thread::hardware_concurrency());
//        for (int i = 0; i < 25; i++)
//        {
//            pool.enqueue([]() { return std::this_thread::sleep_for(std::chrono::seconds(5)); });
//        }
//    }
//    const auto end_time = std::chrono::high_resolution_clock::now();
//    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//    std::cout << "Working hours: " << duration << std::endl;
//
//    return 0;
//}