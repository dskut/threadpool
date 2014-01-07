
#include "pool.h"

class Worker {
public:
    Worker(TaskQueue* const tasks)
        : tasks_(tasks)
    {}

    void operator()() {
        RunnablePtr task = tasks_->pop();
        task->run();
    }

private:
    TaskQueue* const tasks_;
};

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::start(size_t threadsCount) {
    threads_.clear();
    threads_.reserve(threadsCount);
    for (size_t i = 0; i < threadsCount; ++i) {
        threads_.push_back(std::thread(Worker(&tasks_)));
    }
}

void ThreadPool::stop() {
    for (std::thread& thread: threads_) {
        thread.join();
    }
    threads_.clear();
}

void ThreadPool::add(RunnablePtr task) {
    tasks_.push(task);
}
