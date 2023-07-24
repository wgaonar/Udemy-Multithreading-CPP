/*
  Livelock caused by poorly implemented deadlock avoidance
  If the thread cannot get a lock, sleep and try again
  However, all the threads wake up at the same time!!!
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
  bool locked = false;
  while (!locked)
  {
    // Lock mut1
    std::lock_guard<std::mutex> lck_guard(mut1);

    std::cout << "After you Claude!" << "\n";
    std::this_thread::sleep_for(2s);

    // Try to lock mut2
    locked = mut2.try_lock();
  }
  if (locked)
  {
    std::cout << "Thread A has locked both mutexes" << "\n";
  }
}

void funcB()
{
  std::this_thread::sleep_for(10ms);
  bool locked = false;
  while (!locked)
  {
    // Lock mut2
    std::lock_guard<std::mutex> lck_guard(mut2);

    std::cout << "After you Cecil!" << "\n";
    std::this_thread::sleep_for(2s);

    // Try to lock mut1
    locked = mut1.try_lock();
  }
  if (locked)
  {
    std::cout << "Thread B has locked both mutexes" << "\n";
  }
}

int main()
{
  std::thread thrA(funcA);
  std::this_thread::sleep_for(10ms);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}