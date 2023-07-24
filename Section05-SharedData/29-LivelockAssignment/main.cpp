/*
  Use std::scoped_lock to avoid mutual deadlock
  All mutexes are locked in a single operation
  Requires C++17 compiler
*/
#include<iostream>
#include<string>
#include<thread>
#include<mutex>

using namespace std::literals;

std::mutex mut;

int x{0};

void func() 
{
  std::lock_guard<std::mutex> lck_guard(mut);
  while (x == 0) 
  {
    x = 1 - x;
  }
}

int main()
{
  std::thread thr1{func};
  std::thread thr2{func};
	
	thr1.join();
	thr2.join();
}
