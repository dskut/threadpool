threadpool
==========

Simple C++ header-only library implementing thread-pool pattern.

It provides ThreadPool class for running M tasks on N system threads (M can be much greater than N) 
without any system delay or contention.
See http://en.wikipedia.org/wiki/Thread_pool_pattern for more detailed description of this pattern.

It uses boost::lockfree::queue for tasks queue (therefore needs boost >= 1.54). 
Also uses some C++11 features like std::thread, auto and range-based loop.
