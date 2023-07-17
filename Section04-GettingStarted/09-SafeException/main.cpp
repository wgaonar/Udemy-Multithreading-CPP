/*
  Safely destroying an std::thread object
  when an exception is thrown (verbose)
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
  // Create an std::thread object
  std::thread thr(hello);
  
  try
  {
    // Code that might throw an exception
    throw std::exception();

    // No exception if we got here - call join() as usual
    thr.join();
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n'; 

    // Call join() before the thread's destructor is called
    thr.join();
  }
}