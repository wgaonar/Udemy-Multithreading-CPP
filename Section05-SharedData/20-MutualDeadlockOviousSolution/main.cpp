/*
  Avoiding mutual deadlock by writing the threads
  so that they lock the mutexes in the same order
*/
#include<iostream>
#include<thread>
#include<mutex>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
  std::cout << "Thread A trying to lock mutex 1..." << "\n";
  // Acquire lock on mut1
  std::lock_guard<std::mutex> lck_guard1(mut1);
  std::cout << "Thread A has locked mutex 1..." << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread A trying to lock mutex 2..." << "\n";
  // Wait for lock on mut2
  std::lock_guard<std::mutex> lck_guard2(mut2);
  std::cout << "Thread A has locked mutex 2..." << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread A releases all its looks" << "\n";
}

void funcB()
{
  std::cout << "Thread B trying to lock mutex 1..." << "\n";
  // Acquire lock on mut1
  std::lock_guard<std::mutex> lck_guard1(mut1);
  std::cout << "Thread B has locked mutex 1..." << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread B trying to lock mutex 2..." << "\n";
  // Wait for lock on mut2
  std::lock_guard<std::mutex> lck_guard2(mut2);
  std::cout << "Thread B has locked mutex 2..." << "\n";

  // Do some work
  std::this_thread::sleep_for(50ms);

  std::cout << "Thread B releases all its looks" << "\n";
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