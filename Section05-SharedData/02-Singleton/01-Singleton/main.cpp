// Test program for classic Singleton
#include "ClassicSingleton.h"
#include <thread>
#include <vector>

/*
  You must define the static data member outside the class 
  declaration to ensure its existence in the program due that
  it has external linkage
*/ 
Singleton* Singleton::single = nullptr;

void task()
{
  Singleton *single = Singleton::getSingleton();
  std::cout << single << "\n";
}

int main()
{
  std::vector<std::thread> threads;

  // Create the threads
  for (size_t i = 0; i < 10; i++)
  {
    threads.push_back(std::thread(task));
  }

  // Wait to finish the tasks
  for (auto & thr:  threads)
  {
    thr.join();
  }
}

