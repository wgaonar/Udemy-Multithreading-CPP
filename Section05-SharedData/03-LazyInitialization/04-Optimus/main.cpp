/*
  Lazy initialization (multi-threaded)
  It is now thread-safe and uses std::call_one()
  to ensure that one and only one thread initializes the
  object
*/
#include<iostream>
#include<thread>
#include<mutex>

class Test
{
private:
  /* data */
public:
  // Default constructor 
  Test()
  {
    std::cout << "Test constructor called" 
              << " using std::call_one()" << "\n";
  }
  void func() {/*...*/}
};

// Variable to be lazily initialized
Test *ptest = nullptr;

// The flag stores synchronization data
std::once_flag ptest_flag;

void process()
{
  /* 
    Pass a callable object which performs the initialization
    This code will only be executed once and the thread which is 
    executing it, cannot be interrupted
  */
  std::call_once(ptest_flag, 
  []()
  {
    ptest = new Test;
  });
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