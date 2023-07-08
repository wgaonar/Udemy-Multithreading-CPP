// Example of passing an argument to a thread function by value
#include <iostream>
#include <thread>

// Callable object - thread entry point
void hello(std::string str) 
{
  std::cout << str << "\n";
}
int main()
{
  /* 
    Create an std::thread object and pass the 
    task function to the constructor with a
    std::string argument
  */
  std::thread thr(hello,"Hello, Thread with arguments!");

  // Wait for the thread to complete
  thr.join();
}