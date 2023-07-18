// Example with thread ID
#include <iostream>
#include <thread>

// Task function - Displays the thread's ID
void hello() 
{
  std::cout << "Hello from thread with ID: " << std::this_thread::get_id() << "\n";
}
int main()
{
  // Display the main thread's ID
  std::cout << "Main thread has ID: " << std::this_thread::get_id() << "\n";

  // Create an std::thread object
  std::thread thr(hello);

  // Display the child's thread ID
  std::cout << "Hello thread has ID: " << thr.get_id() << "\n"; // 0x######

  // Wait for the thread to complete
  thr.join();

  // Display the child's thread ID again
  std::cout << "Hello thread now has ID: " << thr.get_id() << "\n"; // 0x0
}