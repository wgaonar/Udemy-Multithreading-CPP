// Program to test the concurrent thread pool class

#include "thread_pool.h"
#include <iostream>
#include <future>
#include <string>

using namespace std;
using namespace std::literals;

mutex m;

void task()
{
  lock_guard<std::mutex> lg(m);
  cout << "Thread id: " << this_thread::get_id() << " started task" << "\n";
  this_thread::sleep_for(100ms);
  cout << "Thread id: " << this_thread::get_id() << " finished task" << "\n";
}

int main()
{
  cout << "Creating a thread pool with " << thread::hardware_concurrency() << " threads" << "\n";
  thread_pool pool;

  for (size_t i = 0; i < 10; i++)
  {
    pool.submit(task);
  }
  
  this_thread::sleep_for(5s);
}