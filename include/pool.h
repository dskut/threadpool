#pragma once

#include <vector>
#include <thread>

#include <boost/atomic.hpp>

#include "runnable.h"

const size_t defaultTaskQueueCapacity = 10*1024*1024;

class Worker {
public:
    Worker(TaskQueue* const tasks, boost::atomic<bool>* const isPoolStopped)
        : tasks_(tasks)
        , isPoolStopped_(isPoolStopped)
    {}

    void operator()() {
        while (!	*isPoolStopped_) {
            popTaskAndRun();
        }
        popTaskAndRun();
    }

private:
    void popTaskAndRun() {
        IRunnable* task;
        while (tasks_->pop(task)) {
            task->run();
            delete task;
        }
    }

    TaskQueue* const tasks_;
    boost::atomic<bool>* const isPoolStopped_;
};

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

    void add(IRunnable* task) {
        while (!tasks_.push(task)) {
        }
    }

private:
    std::vector<std::thread> threads_;
    TaskQueue tasks_;
    boost::atomic<bool> isStopped_;
};
