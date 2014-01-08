#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/lockfree/queue.hpp>

class IRunnable {
public:
    virtual ~IRunnable() {}
    virtual void run() = 0;
};

typedef boost::lockfree::queue<IRunnable*> TaskQueue;
