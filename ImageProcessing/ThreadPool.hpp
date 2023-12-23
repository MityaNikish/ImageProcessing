#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <stop_token>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>


class ThreadPool
{
    /*Этот класс предоставляет интерфейс для управления остановкой (cancellation) потока.
    Он связан с механизмом отмены, который позволяет безопасно и эффективно завершать выполнение потока.*/
    std::stop_source stop_source_;
    /*std::jthread представляет собой абстракцию потока выполнения, но с некоторыми дополнительными улучшениями по сравнению
    с более ранними типами потоков, такими как std::thread.
    Основные особенности std::jthread:
		Очистка ресурсов при разрушении.
		Отслеживание состояния выполнения*/
    std::vector<std::jthread> threads_;
	/*std::function<void()> - это объект функционального типа, который представляет собой обертку вокруг различных видов функций,
	способных принимать ноль аргументов и возвращать void.*/
    std::queue<std::function<void()>> tasks_queue_;
    /*Является классом, который предоставляет механизм для синхронизации потоков путем обеспечения доступа к общему ресурсу
    только одним потоком в конкретный момент времени (mutex - обеспечение взаимного исключения).*/
    std::mutex tasks_queue_mutex_;
    /*Предоставляет механизм синхронизации между потоками.
    Она используется вместе с мьютексами (std::mutex) для реализации ожидания и уведомления, что позволяет
    эффективно синхронизировать потоки при работе с разделяемыми данными.*/
    std::condition_variable condition_;
    bool stop_;

public:
    explicit ThreadPool(size_t num_threads) : stop_source_{}, tasks_queue_mutex_{}, condition_{}, stop_(false)
	{
        threads_.reserve(num_threads);
        for (size_t i = 0; i < num_threads; ++i)
        {
            threads_.emplace_back(&ThreadPool::workerThread, this, stop_source_.get_token());
        }
    }

    /*Это объявление функции с использованием автоматического вывода типов(auto) и указанием возвращаемого типа.
    Функция принимает функцию f и ее аргументы args.
    Возвращаемый тип представляет собой std::future, который ассоциирован с типом результата вызова функции f с
    аргументами args.std::invoke_result_t - это утилита C++14, которая возвращает тип результата вызова функции.*/
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
	{
        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(tasks_queue_mutex_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks_queue_.emplace([task]() { (*task)(); });
        }

        condition_.notify_one();
        return res;
    }

    ~ThreadPool()
	{
        {
            std::unique_lock<std::mutex> lock(tasks_queue_mutex_);
            stop_ = true;
        }

        condition_.notify_all();

		//?????????????????????????????????????
        for (std::jthread& worker : threads_) {
            worker.join();
        }
    }

private:
    void workerThread(std::stop_token st)
	{
        while (!st.stop_requested())
        {
            std::unique_lock<std::mutex> lock(tasks_queue_mutex_);
            condition_.wait(lock, [&]() { return stop_ || !tasks_queue_.empty(); });

            if (stop_ && tasks_queue_.empty())
            {
                return;
            }

            auto task = std::move(tasks_queue_.front());
            tasks_queue_.pop();

            lock.unlock();

            task();
        }
    }
};
