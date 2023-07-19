// Example of use std::timed_mutex and try_lock_for()  member function

#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;

// Global mutex object
std::timed_mutex the_mutex;

void task1()
{
  std::cout << "Task1 trying to lock the mutex" << "\n";
  the_mutex.lock();
  std::cout << "Task1 has locked the mutex" << "\n";
  std::this_thread::sleep_for(5s);
  std::cout << "Task1 unlocking the mutex" << "\n";
  the_mutex.unlock();
}

void task2()
{
  std::this_thread::sleep_for(500ms);
  std::cout << "Task2 trying to lock the mutex" << "\n";

  // Try for 1 second to lock de mutex
  while (!the_mutex.try_lock_for(1s))
  {
    // Returned false
    std::cout << "Task2 could not lock the mutex" << "\n";
    // Try again on the next iteration
  }
  // Returned true - the mutex is now locked

  // Start of critical section
  std::cout << "Task2 has locked the mutex" << "\n";
  // End of critical section
  
  std::cout << "Task2 unlocking the mutex" << "\n";
  the_mutex.unlock();
}

int main()
{
  // Start the thread
  std::thread thr1 (task1);
  std::thread thr2 (task2);

  // Wait for the task to complete
  thr1.join();
  thr2.join();
}