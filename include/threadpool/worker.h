#pragma once

#include <threadpool/task.h>
#include <threadpool/queue.h>

namespace threadpool {

class Worker {
public:
    Worker(TaskQueue* const tasks)
        : tasks_(tasks)
    {}

    void operator()() {
        while (true) {
            ITask* task;
            task = tasks_->pop();
            if (task) {
                task->run();
                delete task;
            } else {
                break;
            }
        }
    }

private:
    TaskQueue* const tasks_;
};

} // namespace threadpool
