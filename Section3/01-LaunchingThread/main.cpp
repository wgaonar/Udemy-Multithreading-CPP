// First program with std::thread
#include <iostream>
#include <thread>

// Callable object - thread entry point
void hello() 
{
  std::cout << "Hello, thread!\n";
}
int main()
{
  // Create an std::thread object and pass the task function to the constructor
  std::thread thr(hello);

  // Wait for the thread to complete
  thr.join();
}