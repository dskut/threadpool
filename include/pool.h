#pragma once

#include <vector>
#include <thread>

#include "task_queue.h"

class ThreadPool {
public:
    ~ThreadPool();

    void start(size_t threadsCount);
    void stop();
    void add(RunnablePtr task);

private:
    std::vector<std::thread> threads_;
    TaskQueue tasks_;
};
