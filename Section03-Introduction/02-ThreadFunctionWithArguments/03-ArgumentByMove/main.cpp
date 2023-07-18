// Example of passing an argument to a thread function by move
#include <iostream>
#include <thread>
#include <string>

/*
  Callable object - thread entry point
  Requirers an rvalue argument
*/ 
void func(std::string&& str) 
{
  std::cout << "Ownership of \"" << str << "\" transferred to thread\n";
}
int main()
{
  std::string str {"moveable"};
  std::cout << "Starting a thread\n";

  // Wrap str in a call to std::move()
  std::thread thr(func,std::move(str));

  // Wait for the thread to complete
  thr.join();

  // Verify if the contents of str has been moved
  std::cout << "Do I still have any data?" << " ";
  std::cout << (str.empty() ? "No" : "Yes") << "\n";
}