#pragma once

#include "task.h"

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
        ITask* task;
        while (tasks_->pop(task)) {
            task->run();
            delete task;
        }
    }

    TaskQueue* const tasks_;
    boost::atomic<bool>* const isPoolStopped_;
};

