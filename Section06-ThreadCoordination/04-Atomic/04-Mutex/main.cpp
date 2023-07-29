/* 
  Use std::mutex instead of std::atomic_flag
  which protects a critical section.
  The mutex does the task in sequencial order.
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mut;

void task(int n)
{ 
  std::lock_guard<std::mutex> lck_guard(mut);

  // Start of critical section
  using namespace std::literals;
  std::this_thread::sleep_for(50ms);
  std::cout << "I'm task with the argument " << n << "\n";
  // End of critical section
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