#pragma once

#include <vector>
#include <thread>

#include <boost/atomic.hpp>

#include "task.h"
#include "worker.h"

const size_t defaultTaskQueueCapacity = 1024*1024;

class ThreadPool {
public:
    ThreadPool(size_t queueCapacity = defaultTaskQueueCapacity)
        : tasks_(queueCapacity)
    {}

    ~ThreadPool() {
        stop();
    }

    void start(size_t threadsCount) {
        isStopped_ = false;
        threads_.clear();
        for (size_t i = 0; i < threadsCount; ++i) {
            threads_.push_back(std::thread(Worker(&tasks_, &isStopped_)));
        }
    }

    void stop() {
        isStopped_ = true;
        for (std::thread& thread: threads_) {
            thread.join();
        }
        threads_.clear();
    }

    /**
     * ThreadPool object is responsible for deleting the allocated task object.
     * The caller should not do it himself again.
     */
    void add(ITask* task) {
        while (!tasks_.push(task)) {
        }
    }

private:
    std::vector<std::thread> threads_;
    TaskQueue tasks_;
    boost::atomic<bool> isStopped_;
};
