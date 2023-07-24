/*
  Use std::adopt_lock to avoid mutual deadlock
  All mutexes are locked in a single operation
  using std::lock() function. It requires C++11
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
  std::lock(mut1, mut2);
  std::cout << "Thread A has locked mutexes 1 and 2" << "\n";

  // Adopt the locks
  std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);
  std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread A releasing mutexes 1 and 2" << "\n";
}

void funcB()
{
  std::cout << "Thread B trying to lock mutexes 2 and 1" << "\n";
  std::lock(mut2, mut1);
  std::cout << "Thread B has locked mutexes 2 and 1" << "\n";

  // Adopt the locks
  std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);
  std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);

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