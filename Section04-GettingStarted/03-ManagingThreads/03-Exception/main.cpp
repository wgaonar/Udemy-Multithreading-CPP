// Example of a thread which throws an exception
#include <iostream>
#include <thread>

// Task function for the thread
void hello() 
{
  try 
  {
    // Throw an exception
    throw std::exception();
  }
  catch (std::exception & e)
  {
    std::cerr << "Exception caught: " << e.what() << "\n";
  }
  std::cout << "Hello, Thread" << "\n";
}

int main()
{
  // Create an std::thread object
  std::thread thr(hello);

  // Wait for the thread to complete
  thr.join();

  // Check that the program is still running
  std::cout << "Finished" << "\n";
}