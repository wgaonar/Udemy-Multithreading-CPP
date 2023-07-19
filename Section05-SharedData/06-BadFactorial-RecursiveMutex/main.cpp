/*
  Example of use std::recursive_mutex
  Try to avoid it. It is not recommended!!
*/ 

#include <iostream>
#include <thread>
#include <mutex>

// Global mutex object
std::recursive_mutex rmut;

int bad_factorial (int n)
{
  if (n <= 1)
  {
    std::cout << "Returning " << 1 << "\n";
    return 1;
  }

  // Option 1: This avoids call lock() and unlock() directly.
  std::lock_guard<std::recursive_mutex> lck_guard(rmut);

  // Option 2: Call lock() directly
  // rmut.lock();

  // Start of critical section
  int retval = n * bad_factorial(n-1);
  std::cout << "Returning " << retval << "\n";
  // End of critical section 

  return retval;

  // Option 2: Call unlock() directly
  // rmut.unlock();
}

int main()
{
  // Start the thread
  std::thread thr1 (bad_factorial, 10);
  std::thread thr2 (bad_factorial, 11);

  // Wait for the task to complete
  thr1.join();
  thr2.join();
}