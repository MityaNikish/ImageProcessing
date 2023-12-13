#include "pch.h"
#include <chrono>
#include <iostream>

#include "ImageProcessing.hpp"
#include "InvertColors.hpp"



TEST(Test_InvertColors, AllThreads)
{
    ImageProcessing obj_img_proc;
    obj_img_proc.setStrategy(std::make_unique<InvertColors>());

    cv::Mat inputImage = cv::imread("bird.jpg");

    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat outputImage = obj_img_proc.useStrategy(inputImage);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}


TEST(Test_InvertColors, OneThreads)
{
    ImageProcessing obj_img_proc(1);
    obj_img_proc.setStrategy(std::make_unique<InvertColors>());

    cv::Mat inputImage = cv::imread("bird.jpg");

    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load input image." << std::endl;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    cv::Mat outputImage = obj_img_proc.useStrategy(inputImage);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Working hours: " << duration << std::endl;

    //cv::imwrite("output_image.jpg", outputImage);
}



//#include <vector>
//#include <thread>
//#include <future>
//#include <deque>
//#include <mutex>
//
//std::mutex mtx; // ���������� �������
//
//// ������ ��� ��������� ������ �� � �����
//void multiplyRow(std::vector<int>& row, int rowNumber) {
//    for (int& element : row) {
//        element *= rowNumber;
//    }
//}
//
//// ���������� �������� ���� �������
//class ThreadPool {
//public:
//    explicit ThreadPool(size_t numThreads) : stop(false) {
//        for (size_t i = 0; i < numThreads; ++i) {
//            threads.emplace_back([this] {
//                while (true) {
//                    std::function<void()> task;
//
//                    {
//                        std::unique_lock<std::mutex> lock(queueMutex);
//                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
//
//                        if (stop && tasks.empty()) {
//                            return;
//                        }
//
//                        task = std::move(tasks.front());
//                        tasks.pop_front();
//                    }
//
//                    task();
//                }
//            });
//        }
//    }
//
//    template<class F, class... Args>
//    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
//        using return_type = typename std::result_of<F(Args...)>::type;
//
//        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
//        std::future<return_type> res = task->get_future();
//
//        {
//            std::unique_lock<std::mutex> lock(queueMutex);
//            // don't allow enqueueing after stopping the pool
//            if (stop) {
//                throw std::runtime_error("enqueue on stopped ThreadPool");
//            }
//
//            tasks.emplace_back([task]() { (*task)(); });
//        }
//
//        condition.notify_one();
//        return res;
//    }
//
//    ~ThreadPool() {
//        {
//            std::unique_lock<std::mutex> lock(queueMutex);
//            stop = true;
//        }
//
//        condition.notify_all();
//
//        for (std::thread& worker : threads) {
//            worker.join();
//        }
//    }
//
//private:
//    std::vector<std::thread> threads;
//    std::deque<std::function<void()>> tasks;
//    std::mutex queueMutex;
//    std::condition_variable condition;
//    bool stop;
//};
//
//int main() {
//    const int rows = 50;
//    const int cols = 3;
//    const int numThreads = 12;
//
//    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 2));
//
//    // �������� ���� �������
//    ThreadPool pool(numThreads);
//
//    // ���������� ����� � ��� ��� ��������� ������ ������ �� � �����
//    for (int i = 0; i < rows; ++i) {
//        pool.enqueue(multiplyRow, std::ref(matrix[i]), i);
//    }
//
//    // �������� ���������� ���� �����
//    std::this_thread::sleep_for(std::chrono::seconds(1)); // ��������, ����� ���� ������� ����� �����������
//
//    // ����� ����������
//    for (const std::vector<int>& row : matrix) {
//        for (int element : row) {
//            std::cout << element << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}
