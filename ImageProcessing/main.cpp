#include <iostream>
#include "ImageProcessing.hpp"
#include "InvertColors.hpp"


int main()
{
    ImageProcessing Client;
    Client.setEffect(std::make_unique<InvertColors>());

    cv::Mat inputImage = cv::imread("bird.jpg");

    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    cv::Mat outputImage = Client.applyEffect(inputImage);

    cv::imwrite("output_image.jpg", outputImage);

    return 0;
}