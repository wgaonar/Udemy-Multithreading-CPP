// Example of calling try_lock() in a loop until the mutex is locked
#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;

// Global mutex object
std::mutex task_mutex;

void task1 ()
{
  std::cout << "Task1 trying to lock the mutex" << "\n";
  task_mutex.lock();
  std::cout << "Task1 has locked the mutex" << "\n";
  std::this_thread::sleep_for(500ms);
  std::cout << "Task1 unlocking the mutex" << "\n";
  task_mutex.unlock();
}

void task2 ()
{
  std::this_thread::sleep_for(100ms);
  std::cout << "Task2 trying to lock the mutex" << "\n";
  while (!task_mutex.try_lock())
  {
    std::cout << "Task2 could not lock the mutex" << "\n";
    std::this_thread::sleep_for(100ms);
  }
  std::cout << "Task2 has locked the mutex" << "\n";
  std::this_thread::sleep_for(200ms);
  std::cout << "Task2 unlocking the mutex" << "\n";
  task_mutex.unlock();
}

int main()
{
  // Start the threads concurrently
  std::thread thr1 (task1);
  std::thread thr2 (task2);

  // Wait for the tasks to complete
  thr1.join();
  thr2.join();
}