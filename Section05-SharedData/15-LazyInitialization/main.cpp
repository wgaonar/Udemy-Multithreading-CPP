/*
  Lazy initialization (single-threaded)
  It is not thread-safe. It has a data race because
  the each thread can access the global object at
  the same time.

  The Test constructor can be called more than once 
*/
#include<iostream>
#include<thread>

class Test
{
private:
  /* data */
public:
  // Default constructor 
  Test()
  {
    std::cout << "Test constructor called" << "\n";
  }
  void func() {/*...*/}
};

// Variable to be lazily initialized
Test *ptest = nullptr;

void process()
{
  // First time variable has been used
  if (!ptest)
  {
    // Initialized it
    ptest = new Test;
  }
  // Use it
  ptest->func();
}

int main()
{
  // Create the threads
  std::thread thr1(process);
  std::thread thr2(process);

  // Wait to complete the process
  thr1.join();
  thr2.join();
}