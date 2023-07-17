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

  // Use the lambda expression WITH arguments as the thread's entry point
  std::thread thr2(
    // The first argument is the lambda expression
    [] (int i, int j) 
    {
      std::cout << "The sum of " << i << "(i) and " << j << "(j) is: " << i + j << "\n";
    },
    // The remaining arguments are passed to the lambda expression
    2,3
  );

  // Wait for the threads to complete
  thr.join();
  thr2.join();

  std::cout << "Value new value of i is now: " << i << "\n"; //6
}