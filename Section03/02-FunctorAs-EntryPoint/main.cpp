// Example of std::thread with a functor as entry point
#include <iostream>
#include <thread>

// Functor class with overload () operator
class Hello 
{
public:
  void operator() () 
  {
    std::cout << "Hello, Functor thread!\n";
  }
};

int main()
{
  // Create an object of the functor class
  Hello hello;

  // Pass the function object to the thread's constructor
  std::thread thr(hello);

  // Wait for the thread to complete
  thr.join();
}