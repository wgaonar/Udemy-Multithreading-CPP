// Example of passing a std::thread object to a function
#include <iostream>
#include <thread>

// Task function
void hello() 
{
  using namespace std::literals;
  std::this_thread::sleep_for(1s);  // C++14
  std::cout << "Hello, Thread" << "\n";
  std::cout << "1 seconds after..." << "\n";
}

// Function taking a thread object as argument
// The object must be moved into the argument
void func(std::thread thr)
{
  std::cout << "Received thread with ID: " << thr.get_id() << "\n";
  
  // The function argument now "owns" the system thread
  // It is responsible for calling join()
  thr.join();
} 
int main()
{
  // Create an std::thread object
  // It is a move-only object
  std::thread thr(hello);

  // Display the child's thread ID
  std::cout << "Hello thread has ID " << thr.get_id() << "\n";

  // Pass a named object using std::move()
  func(std::move(thr));

  // Pass a temporary object
  func(std::thread(hello));
}