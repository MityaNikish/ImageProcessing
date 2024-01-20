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
    std::stop_source stop_source_;
    std::vector<std::jthread> threads_;
    std::queue<std::function<void()>> tasks_queue_;
    std::mutex tasks_queue_mutex_;
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

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
	{
        using return_type = std::invoke_result_t<F, Args...>;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f), std::forward<Args>(args)...);

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
