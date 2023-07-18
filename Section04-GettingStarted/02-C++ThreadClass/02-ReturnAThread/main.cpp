// Example of returning a std::thread object from a function
#include <iostream>
#include <thread>

// Task function for the thread
void hello() 
{
  std::cout << "Hello, Thread" << "\n";
}

// Function returning a std::thread object 
std::thread func()
{
  // Start the thread
  std::thread thr(hello);

  // Return a local variable
  return thr;

  // Return a temporary object
  // return std::thread(hello);
} 
int main()
{
  // Call a function which return an std::thread object
  std::thread thr = func();
  std::cout << "Received thread with ID: " << thr.get_id() << "\n";

  // Our thr object now "owns" the system thread
  // It is responsible for calling join()
  thr.join();
}