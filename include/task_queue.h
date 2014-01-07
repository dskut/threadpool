#pragma once

#include <queue>
#include <mutex>
#include "runnable.h"

class TaskQueue {
public:
    void push(RunnablePtr task) {
        std::lock_guard<std::mutex> guard(mutex_);
        tasks_.push(task);
    }

    RunnablePtr pop() {
        std::lock_guard<std::mutex> guard(mutex_);
        RunnablePtr res = tasks_.front();
        tasks_.pop();
        return res;
    }

private:
    std::mutex mutex_;
    std::queue<RunnablePtr> tasks_;
};
