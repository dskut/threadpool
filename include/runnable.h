#pragma once

#include <boost/shared_ptr.hpp>

class IRunnable {
public:
    virtual void run() = 0;
};

// FIXME: use intrusive_ptr
typedef boost::shared_ptr<IRunnable> RunnablePtr;
