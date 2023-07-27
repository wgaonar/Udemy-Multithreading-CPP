/* 
  Use std::atomic_flag to implement a spin lock
  which protects a critical section.
  The atomic_flag does the task in disorder.
*/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// The atomic_flag must be initialized as false
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task(int n)
{
  /* 
    test_and_set()
    Returns true if another thread set the flag 
    Returns false if this thread set the flag 
  */
  while(lock_cout.test_and_set()){}

  // Start of critical section
  using namespace std::literals;
  std::this_thread::sleep_for(50ms);
  std::cout << "I'm task with the argument " << n << "\n";
  // End of critical section

  // Clear the flag, so another thread can set it
  lock_cout.clear();
}

int main()
{
  std::vector<std::thread> threads;

  // Start the tasks
  for (size_t i = 1; i <= 10; i++)
  {
    threads.push_back(std::thread(task,i));
  }
  
  // Join the threads
  for (auto & thr:threads)
  {
    thr.join();
  }
}