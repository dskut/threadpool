#pragma once

#include <vector>
#include <thread>
#include <threadpool/task.h>
#include <threadpool/worker.h>
#include <threadpool/queue.h>

namespace threadpool {

class ThreadPool {
public:
    ~ThreadPool() {
        stop();
    }

    void start(size_t threadsCount) {
        threads_.clear();
        for (size_t i = 0; i < threadsCount; ++i) {
            threads_.push_back(std::thread(Worker(&tasks_)));
        }
    }

    void stop() {
        tasks_.stop();
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
        tasks_.push(task);
    }

private:
    std::vector<std::thread> threads_;
    TaskQueue tasks_;
};

} // namespace threadpool
