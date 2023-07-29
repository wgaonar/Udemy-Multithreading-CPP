// Use a std::lock_guard to avoid scramble output.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;

// Global mutex object
std::mutex task_mutex;

void task (const std::string& str)
{
  // Repeat the output 5 times
  int count {5};
  for (size_t i = 0; i < count; i++)
  {
    try
    {
      // Create an std::lock_guard object
      // This calls task_mutex.lock()
      std::lock_guard<std::mutex> lck_guard (task_mutex);

      // Start of critical section
      for (size_t j = 0; j < str.length(); j++)
      {
        std::cout << str.at(j);
      }
      std::cout << "\n";
      
      // Critical section throws an exception
      throw std::exception();
      // End of critical section

      std::this_thread::sleep_for(50ms);
      
      // The std::lock_guard object calls internally the 
      // task_mutex.unlock() in the destructor ~std::lock_guard
    } 
    catch(const std::exception& e)
    {
      std::cerr << "Exception caught: " << e.what() << '\n';
      // The std::lock_guard object calls internally the 
      // task_mutex.unlock() in the destructor ~std::lock_guard
    }
  }
}

int main()
{
  // Start the threads concurrently
  std::thread thr1 (task, "abc");
  std::thread thr2 (task, "def");
  std::thread thr3 (task, "xyz");

  // Wait for the tasks to complete
  thr1.join();
  thr2.join();
  thr3.join();
}