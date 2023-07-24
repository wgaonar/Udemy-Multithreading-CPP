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

std::mutex mut1, mut2;

void funcA()
{
  std::this_thread::sleep_for(10ms);
  std::cout << "After you Claude!" << "\n";

  // Lock both mutexes
  std::scoped_lock scoped_lck(mut1, mut2);
  std::this_thread::sleep_for(2s);
  std::cout << "Thread A has locked both mutexes" << "\n";
}

void funcB()
{
  std::this_thread::sleep_for(10ms);
  std::cout << "After you Cecil!" << "\n";

  // Lock both mutexes
  std::scoped_lock scoped_lck(mut2, mut1);
  std::this_thread::sleep_for(2s);
  std::cout << "Thread B has locked both mutexes" << "\n";
}

int main()
{
  std::thread thrA(funcA);
  std::this_thread::sleep_for(10ms);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}