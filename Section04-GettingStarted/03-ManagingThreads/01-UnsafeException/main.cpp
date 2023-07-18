/*
  Unsafe exception managing
  What happens to an std::thread object when an exception is thrown?
*/

#include <iostream>
#include <thread>

// Task function for the thread
void hello() 
{
  std::cout << "Hello, Thread" << "\n";
}

int main()
{
  try
  {
    // Create an std::thread object
    std::thread thr(hello);

    // Code that might throw an exception
    throw std::exception();

    // Wait for the thread to complete
    thr.join();
  }
  // Error because the thread try to find a suitable handler (join.()) 
  // within the thread, but there is none inside the hello() function
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n'; 
  }
}