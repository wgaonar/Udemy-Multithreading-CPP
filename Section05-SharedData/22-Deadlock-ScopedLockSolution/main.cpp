/*
  Use std::scoped_lock to avoid mutual deadlock
  All mutexes are locked in a single operation
  Requires C++17 compiler
*/
#include<iostream>
#include<thread>
#include<mutex>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
  std::cout << "Thread A trying to lock mutexes 1 and 2" << "\n";
  std::scoped_lock scoped_lck(mut1, mut2);
  std::cout << "Thread A has locked mutexes 1 and 2" << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread A releasing mutexes 1 and 2" << "\n";
}

void funcB()
{
    std::cout << "Thread B trying to lock mutexes 2 and 1" << "\n";
  std::scoped_lock scoped_lck(mut2, mut1);
  std::cout << "Thread B has locked mutexes 2 and 1" << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread B releasing mutexes 2 and 1" << "\n";
}

int main()
{
  // Create the threads
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  // Wait the tasks to complete
  thrA.join();
  thrB.join();
}