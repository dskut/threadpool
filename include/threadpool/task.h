#pragma once

namespace threadpool {

class ITask {
public:
    virtual ~ITask() {}
    virtual void run() = 0;
};

} // namespace threadpool
