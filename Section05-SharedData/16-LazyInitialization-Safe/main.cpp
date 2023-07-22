/*
  Lazy initialization (multi-threaded)
  It is now thread-safe but it is inefficient
  because all the threads lock and unlock each time
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
              << " using std::unique_lock" << "\n";
  }
  void func() {/*...*/}
};

// Variable to be lazily initialized
Test *ptest = nullptr;
std::mutex mut;

void process()
{
  // Protect ptest
  std::unique_lock<std::mutex> uniq_lck(mut);

  // First time variable has been used
  if (!ptest)
  {
    // Initialized it
    ptest = new Test;
  }
  uniq_lck.unlock();

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