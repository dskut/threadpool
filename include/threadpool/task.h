#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/lockfree/queue.hpp>

namespace threadpool {

class ITask {
public:
    virtual ~ITask() {}
    virtual void run() = 0;
};

typedef boost::lockfree::queue<ITask*> TaskQueue;

} // namespace threadpool
