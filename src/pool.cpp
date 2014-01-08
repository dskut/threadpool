
#include "pool.h"

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

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::start(size_t threadsCount) {
    isStopped_ = false;
    threads_.clear();
    for (size_t i = 0; i < threadsCount; ++i) {
        threads_.push_back(std::thread(Worker(&tasks_, &isStopped_)));
    }
}

void ThreadPool::stop() {
    isStopped_ = true;
    for (std::thread& thread: threads_) {
        thread.join();
    }
    threads_.clear();
}

void ThreadPool::add(IRunnable* task) {
    while (!tasks_.push(task)) {
    }
}
