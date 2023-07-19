/*
  Use a mutex to avoid scramble output.
  The critical section of the code is in the std::cout 
*/
#include <iostream>
#include <thread>
#include <mutex>

// Global mutex object
std::mutex task_mutex;

void print (const std::string& str)
{
  // Repeat the output 5 times
  int count {5};
  for (size_t i = 0; i < count; i++)
  {
    // Lock the mutex before the critical section
    task_mutex.lock();

    // Start of critical section
    for (size_t j = 0; j < str.length(); j++)
    {
      std::cout << str.at(j);
    }
    std::cout << "\n";
    // End of critical section

    // Unlock the mutex after the critical section
    task_mutex.unlock();
  }
}

int main()
{
  // Start the threads concurrently
  std::thread thr1 (print, "abc");
  std::thread thr2 (print, "def");
  std::thread thr3 (print, "xyz");

  // Wait for the tasks to complete
  thr1.join();
  thr2.join();
  thr3.join();
}