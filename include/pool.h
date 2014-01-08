#pragma once

#include <vector>
#include <thread>

#include <boost/atomic.hpp>

#include "task_queue.h"

class ThreadPool {
public:
    ~ThreadPool();

    void start(size_t threadsCount);
    void stop();
    void add(IRunnable* task);

private:
    std::vector<std::thread> threads_;
    TaskQueue tasks_;
    boost::atomic<bool> isStopped_;
};
