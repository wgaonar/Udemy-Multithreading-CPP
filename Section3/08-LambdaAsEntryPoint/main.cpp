// Example of using a lambda expression as a thread's entry point
#include <iostream>
#include <thread>

int main()
{
  int i{3};

  // Use the lambda expression as the thread's entry point
  std::thread thr(
    // The first argument is the lambda expression
    [&i] () {return i *= 2;}
  );

  // Wait for the threads to complete
  thr.join();

  std::cout << "Value of i is now: " << i << "\n";
}