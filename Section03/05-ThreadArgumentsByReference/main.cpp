// Example of passing an argument to a thread function by reference
#include <iostream>
#include <thread>
#include <string>

// Callable object - thread entry point
void hello(std::string& str) 
{
  str = "xyz";
}
int main()
{
  std::string str {"abc"};
  std::cout << "str starts with: "<< str << "\n";

  // Wrap argument in a call to std::ref()
  std::thread thr(hello, std::ref(str));

  // Wait for the thread to complete
  thr.join();

  // Verify that str has been modified
  std::cout << "str is now: " << str << "\n";
}