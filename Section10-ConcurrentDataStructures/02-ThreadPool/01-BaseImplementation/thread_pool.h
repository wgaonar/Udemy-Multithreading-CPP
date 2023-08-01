#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "concurrent_queue_cv.h"
#include <atomic>
#include <thread>
#include <functional>

/* 
  Type alias
  The objects are going to be function objects
  std::function<void()> stores a pointer or lambda
  expression or similar object which takes no arguments
  and returns nothing
*/
using Func = std::function<void()>;

class thread_pool
{
private:
  concurrent_queue_cv<Func> work_queue;
  std::vector<std::thread> threads;
  void worker();
public:
  thread_pool();
  ~thread_pool();
  void submit(Func f);
};

#endif