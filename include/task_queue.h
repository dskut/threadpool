#pragma once

#include <queue>
#include <mutex>
#include <boost/lockfree/queue.hpp>
#include "runnable.h"


/*
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
*/

class TaskQueue: public boost::lockfree::queue<IRunnable*> {
public:
    TaskQueue()
        : boost::lockfree::queue<IRunnable*>(1024*1024)
    {}
};
