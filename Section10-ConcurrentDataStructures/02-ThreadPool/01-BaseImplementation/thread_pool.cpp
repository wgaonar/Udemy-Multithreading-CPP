#include "thread_pool.h"

using namespace std;

// Default constructor
thread_pool::thread_pool()
{
  const unsigned thread_count = thread::hardware_concurrency();
  for (size_t i = 0; i < thread_count; i++)
  {
    threads.push_back(thread{&thread_pool::worker, this});
  }
}

// Destructor
thread_pool::~thread_pool()
{
  for (auto &thr: threads)
  {
    thr.join();
  }
}

void thread_pool::worker()
{
  while (true)
  {
    Func task;
    work_queue.pop(task);
    task();
  }
  
}

void thread_pool::submit(Func f)
{
  work_queue.push(f);
}