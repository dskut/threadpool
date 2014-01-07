
#include <iostream>
#include "pool.h"

class SimpleTask: public IRunnable {
public:
    virtual void run() {
        std::cout << "hello from simple task" << std::endl;
    }
};

int main() {
    const size_t size = 8;
    ThreadPool pool;
    for (size_t i = 0; i < size; ++i) {
        pool.add(RunnablePtr(new SimpleTask));
    }
    std::cout << "tasks added" << std::endl;
    pool.start(size);
    pool.stop();
    std::cout << "pool stopped" << std::endl;
    return 0;
}
