#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <threadpool/task.h>

namespace threadpool {

class TaskQueue {
public:
    TaskQueue()
        : isStopped_(false)
    {}

    void push(ITask* task) {
        std::unique_lock<std::mutex> guard(mutex_);
        queue_.push(task);
        condVar_.notify_all();
    }

    ITask* pop() {
        std::unique_lock<std::mutex> guard(mutex_);
        while (queue_.empty() && !isStopped_) {
            condVar_.wait(guard);
        }
        if (isStopped_) {
            return NULL;
        }
        ITask* res = queue_.front();
        queue_.pop();
        return res;
    }

    void stop() {
        std::unique_lock<std::mutex> guard(mutex_);
        isStopped_ = true;
        condVar_.notify_all();
    }

private:
    std::queue<ITask*> queue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
    bool isStopped_;
};

}
