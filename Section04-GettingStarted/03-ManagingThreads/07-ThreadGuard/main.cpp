/*
  Uses a wrapper class for std::thread
  Ensure safe destruction of an std::thread object
  when an exception is thrown (no-verbose)
*/

#include <iostream>
#include <thread>

class thread_guard
{
private:
  std::thread thr;
public:
  // Constructor takes rvalue reference argument (std::thread is move-only)
  explicit thread_guard(std::thread && thr): thr(std::move(thr)){}

  // Destructor - join the thread if necessary
  ~thread_guard()
  {
    if (thr.joinable())
      thr.join();
  }

  // Delete deep copy constructor to prevent copying
  // Exists but cannot be called
  thread_guard(const thread_guard &) = delete;

  // Delete copy assignment operator to prevent assignment
  // Exits but cannot be called
  thread_guard& operator= (const thread_guard &) = delete;
  
};

// Task function for the thread
void hello() 
{
  std::cout << "Hello, Thread" << "\n";
}

int main()
{
  try
  {
    // Create an std::thread object
    std::thread thr(hello);
    thread_guard thrguard(std::move(thr));

    // Create a temporary object
    // thread_guard thrguard{std::thread(hello)};

    // Code that might throw an exception
    throw std::exception();

    // No need to call join, the thread_guard destructor do it
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n'; 

    // No need to call join, the thread_guard destructor do it
  }
}