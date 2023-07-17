// Example of pausing a thread
#include <iostream>
#include <thread>

using namespace std::literals;

// Task function
void hello() 
{
  // std::this_thread::sleep_for(std::chrono::seconds(2));  // C++11
  std::this_thread::sleep_for(2s);  // C++14
  std::cout << "Hello, Thread" << "\n";
  std::cout << "2 seconds after..." << "\n";
}
int main()
{
  // Create an std::thread object
  std::cout << "Starting a thread..." << "\n";
  std::thread thr(hello);

  // Wait for the thread to complete
  thr.join();
}