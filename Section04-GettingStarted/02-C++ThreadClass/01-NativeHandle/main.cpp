// Example with thread handle
#include <iostream>
#include <thread>

// Task function - thread entry point
void hello() 
{
  std::cout << "Hello, thread!\n";
}
int main()
{
  // Create an std::thread object
  std::thread thr(hello);

  // Display the main child's thread native handle
  std::cout << "Hello thread has native handle: " << thr.native_handle() << "\n"; // 0x######

  // Wait for the thread to complete
  thr.join();

  // Display the main child's thread native handle again
  std::cout << "Hello thread now has native handle: " << thr.native_handle() << "\n"; // 0x0
}