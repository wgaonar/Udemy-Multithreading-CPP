// Example of a thread which throws an uncaught exception
#include <iostream>
#include <thread>

// Task function for the thread
void hello() 
{
  // Throw an exception
  throw std::exception();

  // You have to handle the exception where it is thrown.

  std::cout << "Hello, Thread" << "\n";
}

int main()
{
  try
  {
    // Create an std::thread object
    std::thread thr(hello);
    // Wait for the thread to complete
    thr.join();
  }
  // Error because the thread try to find a suitable handler within
  // the thread, but there is none inside the hello() function
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n'; 
  }

  // Check that the program is still running
  std::cout << "Finished" << "\n";
}