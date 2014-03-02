
#include <iostream>
#include <atomic>
#include <threadpool/pool.h>

using namespace threadpool;

std::atomic_int globalSum(0);

class SimpleTask: public ITask {
public:
    SimpleTask(size_t num)
        : num_(num)
    {}

    virtual void run() {
        globalSum += num_;
    }
private:
    size_t num_;
};

class Producer {
public:
    Producer(ThreadPool* const threadPool, size_t tasksCount)
        : threadPool_(threadPool)
        , tasksCount_(tasksCount)
    {}

    void operator()() {
        for (size_t i = 0; i < tasksCount_; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            threadPool_->add(new SimpleTask(i));
        }
    }
private:
    ThreadPool* const threadPool_;
    const size_t tasksCount_;
};

int main() {
    const size_t poolSize = 8;
    const size_t producersCount = 8;
    const size_t tasksCount = 1000;

    ThreadPool pool;
    pool.start(poolSize);
    std::cout << "pool started" << std::endl;

    std::vector<std::thread> producers;
    for (size_t i = 0; i < producersCount; ++i) {
        producers.push_back(std::thread(Producer(&pool, tasksCount)));
    }
    std::cout << "tasks added" << std::endl;

    for (std::thread& producer: producers) {
        producer.join();
    }
    std::cout << "producers stopped" << std::endl;

    pool.stop();
    std::cout << "pool stopped" << std::endl;

    const int correctSum = tasksCount * (tasksCount - 1) / 2 * producersCount;
    std::cout << "globalSum = " << globalSum << std::endl;
    std::cout << "correct = " << correctSum << std::endl;

    return 0;
}
