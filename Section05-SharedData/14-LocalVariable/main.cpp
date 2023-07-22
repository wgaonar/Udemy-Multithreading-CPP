/*
  Thread-local random number engine
  Ensures that each thread generates the SAME sequence
  (Useful for testing)
*/ 

#include <iostream>
#include <thread>
#include <random>

// Thread-local random number engine
// All the threads will have the same variable
thread_local std::mt19937 mt; 

void func()
{
  // Doubles in the range 0 to 1
  std::uniform_real_distribution<double> dist(0,1);

  for (size_t i = 0; i < 10; i++)
  {
    std::cout << dist(mt) << ", ";  // Generate 10 random numbers
  }
  std::cout << "\n";
}

int main()
{
  std::cout << "Thread 1's random values:" <<"\n";
  std::thread thr1(func);
  thr1.join();  // The thread_local variable is destroyed

  std::cout << "\nThread 2's random values:" << "\n";
  std::thread thr2(func);
  thr2.join();  // The thread_local variable is destroyed
}